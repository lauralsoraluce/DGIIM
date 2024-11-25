document.addEventListener('DOMContentLoaded', () => {
    console.log('Iniciando fetch de ratings...');

    // Seleccionar todos los elementos con la clase 'stars'
    const ele_stars = document.getElementsByClassName('stars');

    for (const ele of ele_stars) {
        const id = ele.dataset._id; // Obtener el ID del producto desde el atributo data-_id

        if (!id) {
            console.error('Elemento sin data-_id:', ele);
            ele.innerHTML = 'No disponible'; // Mostrar un mensaje de error
            continue; // Saltar a la siguiente iteración
        }

        // Fetch al API para obtener el rating inicial del producto
        fetch(`/api/ratings/${id}`)
            .then(response => {
                if (!response.ok) {
                    throw new Error(`Error al obtener el rating para ${id}`);
                }
                return response.json();
            })
            .then(data => {
                console.log(`Datos recibidos para ${id}:`, data);
                renderStars(ele, data.rate, data.count); // Renderizar las estrellas iniciales
                addClickListeners(ele); // Añadir manejadores de eventos para votación
            })
            .catch(error => {
                console.error(`Error al obtener el rating para ${id}:`, error);
                ele.innerHTML = 'No disponible'; // Mostrar un mensaje en caso de error
            });
    }
});


/**
 * Renderiza las estrellas dentro de un elemento.
 * @param {HTMLElement} ele - Elemento que contiene las estrellas.
 * @param {Number} rate - Rating actual.
 */
function renderStars(ele, rate, count) {
    const starCount = 5; // Número total de estrellas
    const fullStars = Math.floor(rate); // Número de estrellas llenas
    const halfStar = rate % 1 >= 0.5; // Verifica si hay media estrella
    const emptyStars = starCount - fullStars - (halfStar ? 1 : 0); // Estrellas vacías

    let starsHTML = '';

    // Crear estrellas llenas
    for (let i = 1; i <= fullStars; i++) {
        starsHTML += `<span class="fa fa-star checked" data-star="${i}"></span>`;
    }

    // Crear media estrella si aplica
    if (halfStar) {
        starsHTML += `<span class="fa fa-star-half-o checked" data-star="${fullStars + 1}"></span>`;
    }

    // Crear estrellas vacías
    for (let i = fullStars + (halfStar ? 2 : 1); i <= starCount; i++) {
        starsHTML += `<span class="fa fa-star" data-star="${i}"></span>`;
    }

    // Mostrar el conteo de votos junto a las estrellas
    starsHTML += `<span class="votos">(${count} votos)</span>`;

    // Asigna el HTML al contenedor y añade eventos
    ele.innerHTML = starsHTML;

    // Asegura que cada estrella tiene el atributo `data-_id`
    for (const star of ele.children) {
        if (star.dataset) {
            star.dataset._id = ele.dataset._id;
        }
    }
}


/**
 * Añade manejadores de clic a las estrellas de un elemento.
 * @param {HTMLElement} ele - Elemento que contiene las estrellas.
 */
function addClickListeners(ele) {
    // Asegúrate de que no agregas los mismos eventos cada vez
    for (const star of ele.children) {
        if (!star.hasListener) {  // Verifica si el evento ya está añadido
            star.addEventListener('click', (evt) => Vota(evt, ele));
            star.hasListener = true;  // Marca que el evento ya ha sido añadido
        }
    }
}

/**
 * Maneja la votación al hacer clic en una estrella.
 * @param {Event} evt - Evento de clic.
 * @param {HTMLElement} ele - Elemento que contiene las estrellas.
 */
function Vota(evt, ele) {
    const id = evt.target.dataset._id; // ID del producto
    const starNumber = parseInt(evt.target.dataset.star); // Estrella seleccionada

    if (!id || !starNumber) {
        console.error('Datos insuficientes para votar:', { id, starNumber });
        return;
    }

    console.log(`Votando ${starNumber} estrellas para el producto ${id}`);

    // Actualización optimista
    const estrellasPrevias = ele.innerHTML; // Guardar estado previo
    renderStars(ele, starNumber, '?'); // Mostrar el cambio optimista con votos desconocidos

    // Hacer el fetch para enviar la votación
    fetch(`/api/ratings/${id}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ rate: starNumber }),
    })
        .then((response) => {
            if (!response.ok) {
                throw new Error('Error en la actualización del servidor');
            }
            return response.json();
        })
        .then((data) => {
            console.log('Actualización en el servidor exitosa:', data);
            renderStars(ele, data.rating.rate, data.rating.count); // Mostrar actualización del servidor
        })
        .catch((error) => {
            console.error('Error en el servidor:', error);
            ele.innerHTML = estrellasPrevias; // Restaurar estado previo en caso de error
        });
}
