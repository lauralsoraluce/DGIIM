import http from 'k6/http';
import { group, check, sleep } from 'k6';
import { __urlencode } from 'k6/encoding';
//import csv from 'k6/x/csv';
//import accesslog from 'k6/x/accesslog';

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
  
    let csvFile = '/home/lauralazaro/Escritorio/DGIIM/TERCERO/ISE/p4/alumnos.csv'; // Ruta del archivo CSV con las credenciales de los alumnos

    csv.readline(csvFile);
    
    let row;
    while ((row=csv.readline(file))){
    	const [login, password] = row.split(',');
    
	    let url = `http://${HOST}:${PORT}/api/v1/auth/login`; // Cambiar por la URL correcta
	    
	    let params = {
	      login: encodeURIComponent(login),
      	password: encodeURIComponent(password),
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
			csv.close(file);

}, { 
  // Configuraciones adicionales para el grupo de alumnos
  onError: 'continue', // Acción a tomar después de un error de sampler
  vus: 4, // Número de hilos (usuarios)
  duration: '15s', // Período de ramp-up en segundos
  iterations: 2, // Número de repeticiones por hilo
  unique: 'per-vu', // Mismo usuario en cada interacción
});

  group('Administradores', function () {
    let csvFile = '/home/lauralazaro/Escritorio/DGIIM/TERCERO/ISE/p4/administradores.csv'; // Ruta del archivo CSV con las credenciales de los administradores

    csv.readline(csvFile);
    
    let row;
    while ((row=csv.readline(file))){
    	const [login, password] = row.split(',');
    

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

			const parserConfig = {
    		parseImages: false,
   		  parser: 'org.apache.jmeter.protocol.http.util.accesslog.TCLogParser',
  		};

  		const logs = accesslog.open('/home/lauralazaro/Escritorio/DGIIM/TERCERO/ISE/p4/apiAlumnos.log', parserConfig);
  		
  		while (accesslog.hasNext(logs)){
  			const log = accesslog.next(logs);

      	// Realiza acciones con los datos del registro de acceso
     		const url = `http://${HOST}:${PORT}${log.url}`;
      	const method = log.method;
     	 	const headers = log.headers;
      	const body = log.body;

      	// Ejecuta la solicitud HTTP correspondiente al registro de acceso
      	const res = http.request(method, url, { headers, body });
  		}

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
