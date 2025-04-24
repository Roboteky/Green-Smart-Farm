import React from "react";
import { TankLevel } from "../components";
import { RainfallAndPumpStatus } from "../containers";
const TankStatus = ({ tankLevels }) => {
  return (
    <div className="w-full col-span-1 phone:row-start-5 tablet:col-start-2 tablet:row-start-2  flex-col-centered gap-2 ">
      <RainfallAndPumpStatus
        isPumpOn={tankLevels?.isPumpOn}
        isRaining={tankLevels?.isRaining}
      />
      <h1 className="font-bold text-xl text-orange-600">WATER TANKS</h1>
      <div className="flex flex-row-centered gap-3 ">
        <TankLevel level={tankLevels.tank1} label="Tank A" />
        <TankLevel level={tankLevels.tank2} label="tank B" />
      </div>
    </div>
  );
};

export default TankStatus;
