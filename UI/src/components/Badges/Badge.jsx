import React from "react";

const Badge = ({ quantity, value }) => {
  return (
    <p className="flex-row-centered gap-2 capitalize w-full ">
      <span className="text-md ">{quantity} :</span>
      <span
        className={`${
          value === "Yes" || value === "true" ? "bg-green-500" : "bg-rose-500"
        } text-black text-bold text-sm w-12 text-center  px-2 rounded-full text-md pt-0.5`}
      >
        {value}
      </span>
    </p>
  );
};

export default Badge;
