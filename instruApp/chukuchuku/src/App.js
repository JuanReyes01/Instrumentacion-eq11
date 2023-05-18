import { useState, useEffect, useCallback } from "react";
import React from "react";
import Header from "./components/Header.js";
import Graph from "./components/Graph.js";
function App(){

const [label, setLabel] = useState([0,0,0,0,0,0,0,0,0,0]);

//individual value states

const [weight, setWeight] = useState(0);
const [rpm, setRpm] = useState(0);
const [temperature, setTemperature] = useState(0);

//list of values 
const [weightData, setWeightData] = useState([0,1,2,3,4,5,6,7,8,9]);
const [rpmData, setRpmData] = useState([0,1,2,3,4,5,6,7,8,9]);
const [temperatureData, setTemperatureData] = useState([0,1,2,3,4,5,6,7,8,9]);

const fetchData = useCallback(async()=>{

  try{
    const response = await fetch('http://192.168.1.1:80/valores');
    const data = await response.json();
    console.log(data);

            //Weight update
            setWeight(data.peso);
            updateWeight(data.peso);
            
            //RPM update
            setRpm(data.rpm);
            updateRPM(data.rpm);
            
            //Temperature update
            setTemperature(data.temp);
            updateTemperature(data.temp)
    
            //Time update
            updateLabel();
    
  }catch(error){
    console.log(error);
  }

}, []);




useEffect(() => {
    const interval = setInterval(fetchData, 2000); // Fetch data every 1 second

    return () => {
      clearInterval(interval); // Cleanup the interval on unmounting
    };
}, []);

const updateWeight = (value) => {
  const updatedList = [...weightData.slice(1,10), value];
  console.log(updatedList)
    setWeightData(updatedList);
}

const updateRPM = (value) => {
    const updatedList = [...rpmData.slice(1, 9), value];
    setRpmData(updatedList);
}

const updateTemperature = (value) => {
    const updatedList = [...temperatureData.slice(1, 9), value];
    setTemperatureData(updatedList);
}

const updateLabel = () => {
  setLabel([...label.slice(1, 9), label[9]+1]);
}
return (
<>
<Header weight={weight} />
  <div className="container mx-auto px-4 py-6">
    <div className="w-full-md mx-auto bg-white rounded-lg shadow-md p-4 mb-4">
      <div className="mb-4">Peso actual: {weight}</div>
      <Graph
        title="Peso"
        data={weightData}
        labels={label}
        color="rgba(75, 255, 192, 1)"
      />
    </div>
    <div className="w-full-md mx-auto bg-white rounded-lg shadow-md p-4 mb-4">
      <div className="mb-4">RPM actual: {rpm}</div>
      <Graph
        title="RPM"
        data={rpmData}
        labels={label}
        color="rgba(211, 97, 53, 1)"
      />
    </div>
    <div className="w-full-md mx-auto bg-white rounded-lg shadow-md p-4 mb-4">
      <div className="mb-4">Temperatura actual: {temperature}</div>
      <Graph
        title="Temperatura"
        data={temperatureData}
        labels={label}
        color="rgba(191, 255, 0, 1)"
      />
    </div>
  </div>
</>

  );
  
            
} 
export default App;