import React from "react";
import { Badge } from "../components";
const RainfallAndPumpStatus = ({ isRaining, isPumpOn }) => {
  return (
    <div className="w-full flex-row-centered gap-4 px-2  rounded-lg text-black dark:text-slate-100">
      <Badge quantity="Rainfall" value={isRaining ? "Yes" : "No"} />
      <Badge quantity="Pump" value={isPumpOn ? "On" : "Off"} />
    </div>
  );
};

export default RainfallAndPumpStatus;
