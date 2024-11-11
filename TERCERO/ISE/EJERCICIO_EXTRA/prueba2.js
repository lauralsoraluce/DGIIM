import http from 'k6/http';
import { sleep, check } from 'k6';
import papaparse from 'https://jslib.k6.io/papaparse/5.1.1/index.js';

// Define las variables de usuario
const HOST = '192.168.56.17';
const PORT = 3000;
const CSV_PATH = 'path/to/credentials.csv';

export let options = {
  vus: 10,
  duration: '30s',
};

// Función para leer las credenciales desde el archivo CSV
function readCredentialsFromCSV() {
  const file = open(CSV_PATH);
  const csvData = papaparse.parse(file);
  const credentials = csvData.data;
  file.close();
  return credentials;
}

// Grupo de usuarios "Alumnos"
export function setup() {
  const credentials = readCredentialsFromCSV();
  return { credentials };
}

export default function (data) {
  const { credentials } = data;

  // Realiza una solicitud POST con parámetros de login y contraseña
  const login = credentials[__ITER % credentials.length][0];
  const password = credentials[__ITER % credentials.length][1];
  const urlEncodedLogin = encodeURIComponent(login);
  const urlEncodedPassword = encodeURIComponent(password);

  const params = {
    login: urlEncodedLogin,
    password: urlEncodedPassword,
  };

  const response = http.post(`http://${HOST}:${PORT}/login`, params);

  // Extrae el token JWT del cuerpo de la respuesta
  const tokenRegExp = /(.+)/;
  const jwtToken = response.body.match(tokenRegExp)[0];

  // Realiza alguna lógica con el token JWT si es necesario
  // ...

  // Espera un tiempo antes de enviar la siguiente solicitud
  sleep(1);

  // Realiza una solicitud GET para recuperar los datos del alumno
  const headers = {
    Authorization: `Bearer ${jwtToken}`,
  };

  const getResponse = http.get(`http://${HOST}:${PORT}/alumnos/datos`, { headers });

  // Realiza alguna lógica con la respuesta de la solicitud GET si es necesario
  // ...

  // Verifica si la solicitud GET fue exitosa
  check(getResponse, {
    'Solicitud GET exitosa': (response) => response.status === 200,
  });
}

