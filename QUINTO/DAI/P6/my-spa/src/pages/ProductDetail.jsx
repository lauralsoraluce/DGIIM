import { useParams } from 'react-router-dom';
import useSWR from 'swr';

const fetcher = (url) => fetch(url).then((res) => res.json());

const ProductDetail = () => {
  const { id } = useParams();
  const { data, error } = useSWR(`https://fakestoreapi.com/products/${id}`, fetcher);

  if (error) return <div>Failed to load product</div>;
  if (!data) return <div>Loading...</div>;

  return (
    <div className="container mx-auto py-10">
      <div className="card bg-base-100 shadow-md p-4 rounded-lg">
        <img
          src={data.image}
          alt={data.title}
          className="h-96 object-contain mx-auto"
        />
        <h1 className="text-2xl font-bold">{data.title}</h1>
        <p className="text-lg text-gray-700">${data.price}</p>
        <p className="mt-4">{data.description}</p>
        <button className="btn btn-primary mt-6">Add to Cart</button>
      </div>
    </div>
  );
};

export default ProductDetail;
