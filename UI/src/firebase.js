// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getFirestore } from "firebase/firestore";

const firebaseConfig = {
  apiKey: "AIzaSyA1RK3XYy-djgFtUkq198sBhqkeTnQ_oxg",
  authDomain: "fir-001-44cf2.firebaseapp.com",
  projectId: "fir-001-44cf2",
  storageBucket: "fir-001-44cf2.appspot.com",
  messagingSenderId: "162477407790",
  appId: "1:162477407790:web:78a97e91da9492b080a9bf",
  measurementId: "G-XH9QGZEJ8V",
};

const app = initializeApp(firebaseConfig);

export const db = getFirestore(app);
