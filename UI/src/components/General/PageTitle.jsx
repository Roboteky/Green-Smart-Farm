import { ToggleButton } from "../../components";
const PageTitle = ({ title, darkToggle, setDarkToggle }) => {
  return (
    <div className="phone:flex phone:items-center phone:justify-between tablet:justify-center   w-full text-center uppercase h-16  pr-2 pl-3 ">
      <span className="phone:text-xl tablet:text-3xl laptop:text-5xl text-slate-700 dark:text-slate-300 font-bold">
        {title}
      </span>
      <ToggleButton darkToggle={darkToggle} setDarkToggle={setDarkToggle} />
    </div>
  );
};

export default PageTitle;
