import useSWR from 'swr';
import { Link } from 'react-router-dom';

const fetcher = (url) => fetch(url).then((res) => res.json());

const Home = () => {
  const { data, error } = useSWR('https://fakestoreapi.com/products', fetcher);

  if (error) return <div>Failed to load products</div>;
  if (!data) return <div>Loading...</div>;

  return (
    <div className="container mx-auto py-10">
      <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-6">
        {data.map((product) => (
          <div
            key={product.id}
            className="card card-compact bg-base-100 shadow-md p-4 rounded-lg flex flex-col justify-between"
          >
            <div className="h-36 flex items-center justify-center">
              <img
                src={product.image}
                alt={product.title}
                className="max-h-full max-w-full object-contain"
              />
            </div>
            <h2 className="text-lg font-bold mt-4">{product.title}</h2>
            <p className="text-gray-500">${product.price}</p>
            <Link to={`/product/${product.id}`}>
              <button className="btn btn-primary mt-4">Buy Now</button>
            </Link>
          </div>
        ))}
      </div>
    </div>
  );
};

export default Home;
