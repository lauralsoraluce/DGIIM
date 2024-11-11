import http from 'k6/http';
import { group, check, sleep } from 'k6';
import { __urlencode } from 'k6/encoding';

// User Defined Variables
export let HOST = '192.168.56.17'; 
export let PORT = '3000'; 

// HTTP Authorization Manager para la autenticación básica
/*export const basicAuth = {
  username: 'etsiiApi', // Reemplaza con el nombre de usuario correcto
  password: 'laApiDeLaETSIIDaLache', // Reemplaza con la contraseña correcta
  base_url: `http://${HOST}:${PORT}/api/v1/auth/login`, // Reemplaza con la URL correcta
  mechanism: 'BASIC',
};*/

export default function () {
  group('Alumnos', function () {
  
    let csvFile = 'path/to/credentials.csv'; // Ruta del archivo CSV con las credenciales de los administradores

    // CSV data set config para cargar las credenciales de los administradores
    let csvConfig = {
      file: csvFile,
      encoding: 'UTF-8',
      ignoreFirstLine: true,
      delimiter: ',',
      quoteChar: '"',
      recycle: true,
      stopOnEOF: false,
      sharing: 'Current thread group',
    };

    let login;
    let password;

    // Leer las credenciales de los administradores del archivo CSV
    let credentials = new DataTable(csvConfig);
    while (credentials.hasNext()) {
      let row = credentials.next();
	      login = row['login'];
	      password = row['password'];
	    let login = 'nombre_de_usuario'; // Nombre de usuario del alumno
	    let password = 'contraseña'; // Contraseña del alumno

	    let url = `http://${HOST}:${PORT}/api/v1/auth/login`; // Cambiar por la URL correcta
	    
	    let params = {
	      login: login,
	      password: password,
	    };

	    let res = http.post(url, params);

	    check(res, {
	      'Login Alumno - status is 200': (r) => r.status === 200,
	    });

	    // Extractor de expresiones regulares para extraer el token JWT
	    let jwtToken = res.body.match(/.+/)[0]; // Aquí se define la expresión regular

	    console.log('JWT Token:', jwtToken);

	    sleep(1);

	    // HTTP request para recuperar los datos del alumno
	    let alumnoURL = `http://${HOST}:${PORT}/api/v1/alumnos/alumno/${__urlencode(login)}`; 
	    
	    let alumnoRes = http.get(alumnoURL, {
	      headers: {
		'Authorization': `Bearer ${jwtToken}`,
	      },
	    });

	    check(alumnoRes, {
	      'Recuperar datos Alumno - status is 200': (r) => r.status === 200,
	    });// Lógica adicional para el grupo de alumnos
    }

}, { 
  // Configuraciones adicionales para el grupo de alumnos
  onError: 'continue', // Acción a tomar después de un error de sampler
  vus: 4, // Número de hilos (usuarios)
  duration: '15s', // Período de ramp-up en segundos
  iterations: 2, // Número de repeticiones por hilo
  unique: 'per-vu', // Mismo usuario en cada interacción
});

  group('Administradores', function () {
    let csvFile = 'path/to/credentials.csv'; // Ruta del archivo CSV con las credenciales de los administradores

    // CSV data set config para cargar las credenciales de los administradores
    let csvConfig = {
      file: csvFile,
      encoding: 'UTF-8',
      ignoreFirstLine: true,
      delimiter: ',',
      quoteChar: '"',
      recycle: true,
      stopOnEOF: false,
      sharing: 'Current thread group',
    };

    let login;
    let password;

    // Leer las credenciales de los administradores del archivo CSV
    let credentials = new DataTable(csvConfig);
    while (credentials.hasNext()) {
      let row = credentials.next();
      login = row['login'];
      password = row['password'];

      // HTTP request para realizar el login de los administradores
      let adminUrl = `http://${HOST}:${PORT}/api/v1/auth/login`; // Cambiar por la URL correcta

      let adminParams = {
      	login: encodeURIComponent(login),
      	password: encodeURIComponent(password),
      };

      let adminRes = http.post(adminUrl, adminParams);

      check(adminRes, {
        'Login Administradores - status is 200': (r) => r.status === 200,
      });

      // Extractor de expresiones regulares para extraer el token JWT
      let jwtToken = adminRes.body.match(/.+/)[0]; // Aquí se define la expresión regular
      console.log('JWT Token:', jwtToken);


      sleep(1);

      // Access Log Sampler para registrar los accesos de los administradores
      let accessLogParams = {
        protocol: 'http',
        server: `${__ENV.HOST}`,
        port: `${__ENV.PORT}`,
        parseImages: false,
        file: 'access.log', // Archivo de registro
      };

      let jwtTokenHeader = {
        'Authorization': `Bearer ${jwtToken}`,
      };

      let jwtTokenRequest = {
        headers: jwtTokenHeader,
      };

      http.request('HEAD', adminUrl, null, jwtTokenRequest); // HEAD request con el encabezado JWT Token

      }
}, {
  // Configuraciones adicionales para el grupo de administradores
  onError: 'continue', // Acción a tomar después de un error de sampler
  vus: 2, // Número de hilos (usuarios)
  duration: '10s', // Período de ramp-up en segundos
  iterations: 1, // Número de repeticiones por hilo
  unique: 'per-vu', // Mismo usuario en cada interacción
});
}
