import react from 'react';
import reactDOM from 'react-dom/client'
import App from './App.js'
import "./styles.css";



//Boilerplate for React 18
const el = document.getElementById('root');
const root = reactDOM.createRoot(el);


root.render(<App/>)