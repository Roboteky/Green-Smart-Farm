import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { Line } from "react-chartjs-2";
import { Data } from "../../utils/data";
ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

const SoilVsAirTempt = ({ darkSide }) => {
  const color = `${darkSide ? "rgb(15 23 42)" : "white"}`;
  const data = {
    labels: Data.map((data) => {
      return `${data.time}`;
    }),
    datasets: [
      {
        label: "Air Temperature",
        data: Data.map((data) => data.airTemperature),
        borderColor: "rgb(255, 99, 132)",
        backgroundColor: "rgba(255, 99, 132, 0.7)",
      },
      {
        label: "Soil Temperature",
        data: Data.map((data) => data.soilTemperature),
        borderColor: "rgb(53, 162, 235)",
        backgroundColor: "rgba(53, 162, 235, 0.7)",
      },
    ],
  };
  return (
    <div className=" phone:col-span-1 flex-row-centered h-auto  tablet:row-start-4 tablet:row-span-2  tablet:col-start-1  tablet:col-span-2  laptop:col-span-2 laptop:row-span-2 rounded-lg dark:bg-slate-500 dark:bg-opacity-20 px-2">
      <Line
        options={{
          responsive: true,
          scales: {
            x: {
              ticks: {
                color: color, // Change the x-axis color here
                weight: "700",
              },
            },
            y: {
              ticks: {
                color: color, // Change the x-axis color here
                weight: "700",
              },
            },
          },
          plugins: {
            dataLabels: {
              color: color,
              backgroundColor: color,
            },
            title: {
              display: true,
              text: "Temperature Chart",
              color: color,
            },
          },
        }}
        data={data}
      />
    </div>
  );
};

export default SoilVsAirTempt;
