import React from "react";
import ReactSpeedometer from "react-d3-speedometer";

export const Gauge = ({ title, value }) => {
  return (
    <div className="rounded-lg col-span-1 h-56 flex-col-centered dark:bg-slate-500 bg-card dark:bg-opacity-20  ">
      <p className="font-bold text-slate-300 uppercase  mr-auto ml-2">
        {title}
      </p>
      <div className="h-48 p-2 ">
        <ReactSpeedometer
          minValue={0}
          maxValue={100}
          width={270}
          ringWidth={40}
          needleHeightRatio={0.75}
          value={value ? value : 0}
          currentValueText={`Percentage : ${value ? value : "Updating..."} %`}
          customSegmentLabels={[
            {
              text: "V. Bad",
              position: "INSIDE",
              color: "#555",
              fontSize: "12px",
            },
            {
              text: "Bad",
              position: "INSIDE",
              color: "#555",
            },
            {
              text: "Ok",
              position: "INSIDE",
              color: "#555",
              fontSize: "19px",
            },
            {
              text: "Good",
              position: "INSIDE",
              color: "#555",
            },
            {
              text: "V. Good",
              position: "INSIDE",
              color: "#555",
              fontSize: "12px",
            },
          ]}
          needleTransitionDuration={3333}
          needleTransition="easeElastic"
          needleColor={"#57575c"}
          textColor={"#d8dee9"}
        />
      </div>
    </div>
  );
};

export default Gauge;
