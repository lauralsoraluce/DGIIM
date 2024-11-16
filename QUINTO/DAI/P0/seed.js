import mongoose from 'mongoose';
import { MongoClient } from 'mongodb';
import Usuarios from './model/usuarios.js';  // Asegúrate de importar el modelo de usuario
import bcrypt from 'bcrypt';

console.log('🏁 seed.js ----------------->');

// del archivo .env
const USER_DB = process.env.USER_DB;
const PASS = process.env.PASS;

const url = `mongodb://${USER_DB}:${PASS}@localhost:27017`;
const client = new MongoClient(url);

const dbName = 'myProject';

// función asíncrona para insertar datos en la colección
async function Inserta_datos_en_colección(coleccion, apiUrl) {
	try {
	  const response = await fetch(apiUrl);
	  if (!response.ok) {
		throw new Error(`Error en la solicitud a ${apiUrl}: ${response.status} ${response.statusText}`);
	  }
	  const datos = await response.json();
  
	  if (!Array.isArray(datos)) {
		throw new Error(`Datos obtenidos de ${apiUrl} no son un array.`);
	  }
  
	  await client.connect();
	  const db = client.db(dbName);
	  const collection = db.collection(coleccion);
  
	  await collection.deleteMany({});  // Vaciar la colección
  
	  // Si la colección es 'usuarios', encriptar las contraseñas
	  if (coleccion === 'usuarios') {
		const usuarios = await Promise.all(datos.map(async (usuarioData) => {
		  const nombre = `${usuarioData.name.firstname} ${usuarioData.name.lastname}`;
		  const salt = await bcrypt.genSalt(8);  // Genera el salt de forma manual
		  const hashedPassword = await bcrypt.hash(usuarioData.password, salt);  // Encripta la contraseña
  
		  return {
			username: usuarioData.username,
			password: hashedPassword,
			email: usuarioData.email,
			nombre: nombre,
		  };
		}));
  
		const result = await collection.insertMany(usuarios);
	  } else {
		const resultado = await collection.insertMany(datos);
	  }
  
	  return `${datos.length} datos traídos para ${coleccion}`;
	} catch (err) {
	  console.error(`Error en Inserta_datos_en_colección: ${err.message}`);
	  throw err;
	} finally {
	  await client.close();  // Cierra la conexión a MongoDB
	}
  }

// Inserción consecutiva en productos y usuarios
Inserta_datos_en_colección('productos', 'https://fakestoreapi.com/products')
  .then((r) => console.log(`Todo bien: ${r}`))
  .then(() => Inserta_datos_en_colección('usuarios', 'https://fakestoreapi.com/users'))
  .then((r) => console.log(`Todo bien: ${r}`))
  .catch((err) => console.error('Algo mal: ', err.errorResponse));

console.log('Lo primero que pasa');

async function consulta_productos_precio_mayor_a_100() { // Asíncrona para que no bloquee el programa
  const db = client.db(dbName); // Nos conectamos a la base de datos
  const productos = db.collection('productos'); // Seleccionamos la tabla productos
	
	try {
  const resultado = await productos.find({ price: { $gt: 100 } }).toArray(); // Busca las filas que tengan el campo de price a un valor "greater than" 100. Lo convierte a array
  console.log('Productos con precio mayor a 100:', resultado);
  } catch (error){
  	console.error(`ERROR: ${error}`);
  }
}

consulta_productos_precio_mayor_a_100().then(() => console.log('---'));

async function consulta_productos_winter() { 
	const db = client.db(dbName);
	const productos = db.collection('productos');
	
	try {
		const resultado = await productos.find({ description: { $regex: 'winter', $options: 'i' } }, { sort: { price: 1 } }).toArray(); // El 1 indica orden ascendente, la opción i indica mayusculas o minúsculas indistintamente
		console.log('Productos cuya descripción contega Winter ordenados por precio ascendente:', resultado);
	} catch (error){
		console.error(`ERROR: ${error}`);
	}
}

consulta_productos_winter().then(() => console.log('---'));

async function consulta_productos_joyeria_rating() { 
	const db = client.db(dbName);
	const productos = db.collection('productos');
	
	try {
		const resultado = await productos.find({ category: 'jewelery'}, { sort: { 'rating.rate': -1 } }).toArray(); // El -1 indica orden descendente, usamos 'rating.rate' porque es un campo anidado
		console.log('Productos de joyería ordenados por rating:', resultado);
	} catch (error){
		console.error(`ERROR: ${error}`);
	}
}

consulta_productos_joyeria_rating().then(() => console.log('---'));

function suma_count_total(productos){
	let total = 0;
	for (let i=0; i<productos.length; i++){
		total=total+productos[i].rating.count;
	}
	return total;
}
/* Creo una función que, dado un array de productos, se encargue de sumar todos los valores del campo rating.count y devuelva el resultado. No necesita ser asíncrona, porque sólo suma sobre valores ya cargados en memoria, no hace consultas a la base de datos. */
		
async function consulta_ratings_totales() { 
	const db = client.db(dbName);
	const productos = db.collection('productos');
	
	try {
		const productosArray = await productos.find().toArray(); //La función de suma espera un array que poder recorrer
		const resultado = suma_count_total(productosArray);
		console.log('Numero total de ratings:', resultado);
	} catch (error){
		console.error(`ERROR: ${error}`);
	}
}

consulta_ratings_totales().then(() => console.log('---'));

async function consulta_rating_categoria() { 
	const db = client.db(dbName);
	const productos = db.collection('productos');
	
	try {
		const categorias = await productos.distinct('category'); // Selecciona todos los valores diferentes del campo category
		
		let sum = [];
		for (let i=0; i<categorias.length; i++){ // Para cada categoría, localizamos los productos que pertenecen a dicha categoría
			let prod_cat = await productos.find({ category: categorias[i] }).toArray();
			sum[i]=0; // IMP: Inicializamos a 0 el array de sumas medias
			for (let j=0; j<prod_cat.length; j++){ // Para cada producto, sumamos todos sus ratings
				sum[i]=sum[i]+prod_cat[j].rating.rate;
			}
			sum[i]=sum[i]/prod_cat.length; // Una vez sumados todos, dividimos entre el número de productos para hallar la media
		}
		
		for (let i=0; i<categorias.length; i++){
			console.log('Rating medio de', categorias[i], ':', sum[i]);
		}
	} catch (error){
		console.error(`ERROR: ${error}`);
	}
}

consulta_rating_categoria().then(() => console.log('---'));

async function consulta_usuarios_sin_digitos() {
	const db = client.db(dbName);
	const usuarios = db.collection('usuarios');
	let num = 0;
	
	try {
		const resultado = await usuarios.find().toArray();
		for (let i=0; i<resultado.length; i++){
			if (resultado[i].password.match(/\d/) !== null){ // La función match busca si el string al que se la aplicamos contiene una cierta expresión regular, en este caso, algún dígito
				num=num+1;
			}
		}
		console.log('Número de usuarios sin dígito en la contraseña:', num);
	} catch (error){
		console.error(`ERROR: ${error}`);
	}
}

consulta_usuarios_sin_digitos().then(() => console.log('---'));