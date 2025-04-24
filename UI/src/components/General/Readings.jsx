const Readings = ({ value, reading, unit }) => {
  return (
    <div className="w-1/2 flex-col-centered gap-2">
      <div className="capitalize text-xl">{value}</div>
      <div>
        <span className="text-6xl mr-1">{reading}</span>
        <span className="text-2xl">{unit}</span>
      </div>
    </div>
  );
};

export default Readings;
