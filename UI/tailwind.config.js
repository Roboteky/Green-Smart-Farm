/** @type {import('tailwindcss').Config} */
export default {
  darkMode: "class",
  content: ["./index.html", "./src/**/*.{js,ts,jsx,tsx}"],
  theme: {
    screens: {
      phone: "300px",
      tablet: "568px",
      laptop: "1024px",
      desktop: "1280px",
    },
    extend: {
      colors: {
        primary: "#1851E1",
        secondary: "#1C4DCB",
        background: "#D6D5E5",
        navy: "#002D62",
        chelseaBlue: "#034694",
        card: "#205295",
      },
    },
  },
  plugins: [],
};
