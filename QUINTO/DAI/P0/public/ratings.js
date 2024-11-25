document.addEventListener('DOMContentLoaded', () => {
    console.log('Iniciando fetch ...');
    const ele_stars = document.getElementsByClassName('stars');
    console.log('Cantidad de elementos .stars encontrados:', ele_stars.length);
  
    for (const ele of ele_stars) {
      const id = ele.dataset._id;
      console.log('Procesando elemento con data-_id:', id);
  
      if (!id) {
        console.error('Elemento sin data-_id:', ele);
        ele.innerHTML = 'No disponible';
        continue;
      }
  
      // Fetch del API
      fetch(`/api/ratings/${id}`)
        .then(response => response.json())
        .then(data => {
          console.log('Datos recibidos para', id, ':', data);
  
          const rate = data.rate;
          const fullStars = Math.floor(rate);
          const halfStar = rate % 1 >= 0.5;
          const emptyStars = 5 - fullStars - (halfStar ? 1 : 0);
  
          let starsHTML = '';
          starsHTML += '<span class="fa fa-star checked"></span>'.repeat(fullStars);
          if (halfStar) starsHTML += '<span class="fa fa-star-half-o checked"></span>';
          starsHTML += '<span class="fa fa-star"></span>'.repeat(emptyStars);
  
          ele.innerHTML = starsHTML;
        })
        .catch(error => {
          console.error('Error al obtener el rating para', id, ':', error);
          ele.innerHTML = 'No disponible';
        });
    }
  });
  