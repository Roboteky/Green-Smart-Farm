import React, { useState, useEffect } from "react";
import { collection, addDoc, getDocs } from "firebase/firestore";
import { db } from "../../firebase";
import { PageTitle } from "../../components";
import "../../App.css";

const Todo = () => {
  const [todo, setTodo] = useState("");
  const [todos, setTodos] = useState([]);

  useEffect(() => {
    const interval = setInterval(() => {
      fetchRealTimeData();
    }, 6000);

    return () => {
      clearInterval(interval);
    };
  }, []);
  // CREATING DATA FIREBASE
  //========================
  const addTodo = async (e) => {
    e.preventDefault();
    try {
      const docRef = await addDoc(collection(db, "farm"), {
        anything: todo,
      });
      console.log("Document written with ID: ", docRef.id);
    } catch (e) {
      console.error("Error adding document: ", e);
    }
  };

  //   READING DATA FIRESTORE
  //==========================
  // READING DATA FIRESTORE
  //========================
  const fetchRealTimeData = async () => {
    await getDocs(collection(db, "farm")).then((querySnapshot) => {
      const newData = querySnapshot.docs.map((doc) => ({
        ...doc.data(),
        id: doc.id,
      }));
      setTodos(newData);
      console.log(todos, newData);
    });
  };

  return (
    <section className="todo-container debug w-3/4 border-cyan-100 mx-auto flex-col-centered">
      <PageTitle title="Todo App" />
      <div className="flex-row-centered gap-5 uppercase h-16 px-3">
        <label for="text" className="text-white ">
          Activity
        </label>
        <input
          type="text"
          placeholder="Input Activity"
          onChange={(e) => setTodo(e.target.value)}
          className="h-10 rounded-md w-64 px-2"
        />
        <div>
          <button
            type="submit"
            className="bg-black text-white w-48 h-10 "
            onClick={addTodo}
          >
            Submit
          </button>
        </div>
      </div>
    </section>
  );
};

export default Todo;
