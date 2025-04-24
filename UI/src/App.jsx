import { useEffect, useState } from "react";
import { collection, addDoc, getDocs } from "firebase/firestore";
import { db } from "./firebase";
import {
  SoilVsAirTempt,
  Gauge,
  PhGauge,
  PageTitle,
  ToDo,
  ToggleButton,
} from "./components";
import { TankStatus, VoltageAndCurrentReadings } from "./containers";
import "./App.css";
const App = () => {
  const [realTimeData, setRealTimeData] = useState({});
  const [pvVoltage, setPvVoltage] = useState(0);
  const [pvCurrent, setPvCurrent] = useState(0);
  const [tankLevels, setTankLevels] = useState({
    tank1: 0,
    tank2: 0,
    isRaining: false,
    isPumpOn: false,
  });
  const [value, setValue] = useState(5);
  const [theme, setTheme] = useState(localStorage.theme);
  const [darkSide, setDarkSide] = useState(theme === "light" ? true : false);

  const toggleDarkMode = (checked) => {
    setTheme(colorTheme);
    setDarkSide(checked);
  };
  // On page load or when changing themes, best to add inline in `head` to avoid FOUC
  const colorTheme = theme === "dark" ? "light" : "dark";

  useEffect(() => {
    const root = window.document.documentElement;
    root.classList.remove(colorTheme);
    root.classList.add(theme);
    // Save current theme to local storage
    localStorage.setItem(`theme`, theme);
  }, [theme, colorTheme]);
  useEffect(() => {
    const interval = setInterval(() => {
      fetchRealTimeData();
    }, 5500);

    return () => {
      clearInterval(interval);
    };
  }, []);

  const fetchRealTimeData = async () => {
    await getDocs(collection(db, "farm")).then((querySnapshot) => {
      const newData = querySnapshot.docs.map((doc) => ({
        ...doc.data(),
        id: doc.id,
      }));
      setRealTimeData(newData[0]);
      setPvVoltage(newData[0]?.pvVoltage);
      setPvCurrent(newData[0]?.pvCurrent);
      setTankLevels({
        tank1: newData[0]?.tank1Level,
        tank2: newData[0]?.tank2Level,
        isRaining: newData[0]?.raining,
        isPumpOn: newData[0]?.pumpOn,
      });

      console.log(newData[0]);
    });
  };

  return (
    <div
      className={`flex flex-col w-full min-h-screen dark:bg-navy bg-slate-100 `}
    >
      <PageTitle
        title="Mkulima Dashboard"
        darkToggle={darkSide}
        setDarkToggle={toggleDarkMode}
      />
      <div className="grid phone:grid-cols-1 tablet:grid-cols-2 laptop:grid-cols-3 gap-4 min-h-screen p-4">
        <Gauge title="humidity" value={realTimeData?.airHumidity} />
        <Gauge title="moisture" value={realTimeData?.soilMoisture} />
        <PhGauge title="Ph level" value={realTimeData?.soilPH} />
        <SoilVsAirTempt darkSide={darkSide} />
        <div className="col-span-1 phone:row-start-4 tablet:col-start-2 tablet:col-span-1 tablet:row-start-2 laptop:row-start-2 laptop:col-start-3 laptop:col-span-1 rounded-lg flex-col-centered gap-2">
          <div className="w-full tablet:hidden laptop:block">
            <VoltageAndCurrentReadings realTimeData={realTimeData} />
          </div>
          <TankStatus value={value} tankLevels={tankLevels} />
        </div>

        <div className="w-full phone:hidden tablet:block tablet:col-span-2 laptop:hidden">
          <VoltageAndCurrentReadings
            pvVoltage={pvVoltage}
            pvCurrent={pvCurrent}
            value={value}
          />
        </div>
      </div>
      {/* <ToDo /> */}
    </div>
  );
};

export default App;
