import React from "react";
import { Readings } from "../components";
const VoltageAndCurrentReadings = ({ realTimeData, pvVoltage, pvCurrent }) => {
  console.log(pvCurrent);
  console.log(pvVoltage);
  return (
    <div className=" w-full flex dark:bg-slate-500 dark:bg-opacity-20 bg-card p-1 gap-3 rounded-lg text-white ">
      <Readings value="voltage" reading={pvVoltage} unit="V" />
      <Readings value="current" reading={pvCurrent} unit="mA" />
    </div>
  );
};

export default VoltageAndCurrentReadings;
