import React from "react";
const ToggleButton = ({ darkToggle, setDarkToggle }) => {
  return (
    <div
      className="phone:w-9 phone:h-9 rounded-full hover:bg-slate-400 hover:bg-opacity-30 flex-row-centered border-2 border-cyan-500 phone:relative tablet:absolute tablet:top-2 tablet:right-2"
      onClick={() => setDarkToggle(!darkToggle)}
    >
      <span>
        {!darkToggle ? (
          <svg
            xmlns="http://www.w3.org/2000/svg"
            fill="none"
            viewBox="0 0 24 24"
            strokeWidth={1.5}
            stroke="currentColor"
            className="phone:w-4 phone:h-4 tablet:w-6 tablet:h-6 text-white"
          >
            <path
              strokeLinecap="round"
              strokeLinejoin="round"
              d="M12 3v2.25m6.364.386l-1.591 1.591M21 12h-2.25m-.386 6.364l-1.591-1.591M12 18.75V21m-4.773-4.227l-1.591 1.591M5.25 12H3m4.227-4.773L5.636 5.636M15.75 12a3.75 3.75 0 11-7.5 0 3.75 3.75 0 017.5 0z"
            />
          </svg>
        ) : (
          <svg
            xmlns="http://www.w3.org/2000/svg"
            viewBox="0 0 20 20"
            fill="currentColor"
            className="phone:w-4 phone:h-4 tablet:w-6 tablet:h-6 text-primary "
          >
            <path
              fill-rule="evenodd"
              d="M7.455 2.004a.75.75 0 01.26.77 7 7 0 009.958 7.967.75.75 0 011.067.853A8.5 8.5 0 116.647 1.921a.75.75 0 01.808.083z"
              clip-rule="evenodd"
            />
          </svg>
        )}
      </span>
    </div>
  );
};

export default ToggleButton;
