import { callback } from "react";
import React, { useState } from "react";

    const Sidebar = (props) => {
    //Sidebar open toggle
    const [isOpen, setIsOpen] = useState(false);

    //Is step Motor on
    const [isOn, setIsOn] = useState(false);

    //Is RPM value valid
    const [isRpmValid, setIsRpmValid] = useState(false);

    //Model open handle states
    //Modal for liguids
    const [isModalLiquidOpen, setIsModalLiquidOpen] = useState(false);
    //Modal for RPM
    const [isModalRPMOpen, setIsModalRPMOpen] = useState(false);

    //React states for inputs
    const [liquidInput, setLiquidInputValue] = useState(props.weight);
    const [rpmInput, setRpmInputValue] = useState(70);

    //Sidebar open toggle function
    const handleToggleSidebar = () => {
        setIsOpen(!isOpen);
    };

    //Modal open toggle function
    function handleLiquidModalToggle() {
        setIsModalLiquidOpen(!isModalLiquidOpen);
    }
    function handleRpmModalToggle() {
        setIsModalRPMOpen(!isModalRPMOpen);
    }

    //Handle changes on the inputs
    function handleLiquidInputChange(event) {
        if (event.target.value === "") setLiquidInputValue(0);
        else setLiquidInputValue(parseInt(event.target.value));
    }

    function handleRpmInputChange(event) {
        if (event.target.value < 70 || event.target.value > 200)
        setIsRpmValid(false);
        else setIsRpmValid(true);
        if (event.target.value === "") setRpmInputValue(70);
        else setRpmInputValue(parseInt(event.target.value));
    }

    //Objective value of liquid in the system
    async function handleLiquidChange(e) {
        e.preventDefault();

        const data = liquidInput;

        try {
        const response = await fetch("192.164.5.5:8081", {
            method: "PUT",
            headers: {
            "Content-Type": "application/json",
            },
            body: JSON.stringify(data),
        });

        if (response.ok) {
            // POST request was successful
            console.log("Post created successfully!");
        } else {
            // Handle error case
            console.log("Failed to create post.");
        }
        } catch (error) {
        console.log("Error:", error);
        }
    }

    //Objective value of rpm in the system
    async function handleRpmChange() {
        if (isRpmValid) {
        //PUT para rpm deseado
        try{
            let headers ={
            "Content-Type": "application/json",
            }
            let body = JSON.stringify({rpm: rpmInput})
            let response = await fetch("http://192.168.1.1:80/rpmDeseado", {method: "PUT", headers: headers, body: body})
            callback(await response.json());
            if(response.ok){
            console.log("RPM changed successfully!");
            }else{
            console.log("Failed to change RPM.");
            }
        }catch(error){
            console.log("Error:", error);

        }
        

        }
    }


    async function handleToggleOn() {
        // if (isOn) {
        // const data = rpmInput;

        // try {
        //     const response = await fetch("192.164.5.5:8081", {
        //     method: "POST",
        //     headers: {
        //         "Content-Type": "application/json",
        //     },
        //     body: JSON.stringify(data),
        //     });

        //     if (response.ok) {
        //     // POST request was successful
        //     console.log("Post created successfully!");
        //     } else {
        //     // Handle error case
        //     console.log("Failed to create post.");
        //     }
        // } catch (error) {
        //     console.log("Error:", error);
        // }
        // } else {
        // const data = 0;

        // try {
        //     const response = await fetch("192.164.5.5:8081", {
        //     method: "POST",
        //     headers: {
        //         "Content-Type": "application/json",
        //     },
        //     body: JSON.stringify(data),
        //     });

        //     if (response.ok) {
        //     // POST request was successful
        //     console.log("Post created successfully!");
        //     } else {
        //     // Handle error case
        //     console.log("Failed to create post.");
        //     }
        // } catch (error) {
        //     console.log("Error:", error);
        // }
        // }

        setIsOn((isOn) => !isOn);
    }

    return (
        <>
        <button
            onClick={handleToggleSidebar}
            className="fixed top-1 right-2 z-50 bg-white py-2 px-3 rounded-lg shadow-md text-blue-500 font-bold focus:outline-none text-3xl"
        >
            ≡
        </button>
        {isOpen && (
            <div
            onClick={handleToggleSidebar}
            className="fixed top-0 left-0 z-40 w-full h-full bg-black opacity-50"
            />
        )}
        <div
            className={`fixed top-0 right-0 z-50 w-1/2 h-full bg-blue-500 transition-all duration-300 ${
            isOpen ? "translate-x-0" : "translate-x-full"
            }`}
        >
            <div className="flex flex-col justify-center items-center h-full px-4">
            <button
                className="w-full py-2 bg-white text-blue-500 rounded-lg mb-4 focus:outline-none hover:bg-slate-100"
                onClick={handleLiquidModalToggle}
            >
                Agregar Liquido
            </button>
            <button
                className="w-full py-2 bg-white text-blue-500 rounded-lg mb-4 focus:outline-none hover:bg-slate-100"
                onClick={handleRpmModalToggle}
            >
                Cambiar RPM
            </button>
            <button
                className={`block mb-4 w-full py-4 px-4 text-white rounded-md focus:outline-none focus:ring-2 ${
                isOn
                    ? "bg-red-500 hover:bg-red-600 focus:ring-red-400"
                    : "bg-green-500 hover:bg-green-600 focus:ring-gray-400"
                }`}
                onClick={handleToggleOn}
            >
                {isOn ? "Turn Off" : "Turn On"}
            </button>
            </div>
        </div>

        {/*Modal cambiar cantidad de liquido*/}
        {isModalLiquidOpen ? (
            <div className="fixed z-50 inset-0 overflow-y-auto">
            <div className="flex items-center justify-center min-h-screen px-4 pt-4 pb-20 text-center">
                <div
                className="fixed inset-0 transition-opacity bg-gray-500 bg-opacity-75"
                aria-hidden="true"
                ></div>
                <div className="relative z-10 w-full max-w-md mx-auto my-auto bg-white rounded-md shadow-lg">
                <div className="px-4 py-2 bg-gray-200 rounded-t-md">
                    <h2 className="text-lg font-bold">Agregar Liguido</h2>
                </div>
                <div className="p-4">
                    <div className="flex items-center justify-center">
                    <input
                        type="number"
                        max={1000}
                        min={0}
                        value={liquidInput}
                        onChange={handleLiquidInputChange}
                        className="bg-gray-400 text-white rounded-l-lg p-2 focus:outline-none"
                    />
                    <div className="bg-gray-400 rounded-r-lg px-2 py-2 flex items-center justify-center">
                        <span className="text-white font-bold">g</span>
                    </div>
                    </div>
                </div>
                <div className="px-4 py-2 bg-gray-200 rounded-b-md">
                    <button
                    type="button"
                    className="inline-flex justify-center px-4 py-2 text-sm font-medium text-white bg-green-500 border border-transparent rounded-md hover:bg-green-600 focus:outline-none focus:ring-2 focus:ring-green-400"
                    onClick={handleLiquidChange}
                    >
                    Submit
                    </button>
                    <button
                    type="button"
                    className="inline-flex justify-center px-4 py-2 ml-4 text-sm font-medium text-gray-700 bg-gray-300 border border-transparent rounded-md hover:bg-gray-400 focus:outline-none focus:ring-2 focus:ring-gray-400"
                    onClick={() => setIsModalLiquidOpen(false)}
                    >
                    Cancel
                    </button>
                </div>
                </div>
            </div>
            </div>
        ) : null}
        {/*Modal cambiar los RPMs*/}
        {isModalRPMOpen ? (
            <div className="fixed z-50 inset-0 overflow-y-auto">
            <div className="flex items-center justify-center min-h-screen px-4 pt-4 pb-20 text-center">
                <div
                className="fixed inset-0 transition-opacity bg-gray-500 bg-opacity-75"
                aria-hidden="true"
                ></div>
                <div className="relative z-10 w-full max-w-md mx-auto my-auto bg-white rounded-md shadow-lg">
                <div className="px-4 py-2 bg-gray-200 rounded-t-md">
                    <h2 className="text-lg font-bold">Cambiar RPM</h2>
                </div>
                <div className="p-4">
                    <div className="flex items-center justify-center">
                    <input
                        type="number"
                        max={200}
                        min={70}
                        value={rpmInput}
                        onChange={handleRpmInputChange}
                        className="bg-gray-400 text-white rounded-l-lg p-2 focus:outline-none"
                    />
                    <div className="bg-gray-400 rounded-r-lg px-2 py-2 flex items-center justify-center">
                        <span className="text-white font-bold">rpm</span>
                    </div>
                    </div>
                </div>
                <div className="px-4 py-2 bg-gray-200 rounded-b-md">
                    <button
                    type="button"
                    className={`inline-flex justify-center px-4 py-2 text-sm font-medium text-white border border-transparent rounded-md focus:outline-none focus:ring-2
                                ${
                                isRpmValid
                                    ? "bg-green-500 hover:bg-green-600 focus:ring-gray-400"
                                    : "bg-red-500 hover:bg-red-600 focus:ring-red-400"
                                }`}
                    onClick={handleRpmChange}
                    >
                    Submit
                    </button>
                    <button
                    type="button"
                    className="inline-flex justify-center px-4 py-2 ml-4 text-sm font-medium text-gray-700 bg-gray-300 border border-transparent rounded-md hover:bg-gray-400 focus:outline-none focus:ring-2 focus:ring-gray-400"
                    onClick={() => setIsModalRPMOpen(false)}
                    >
                    Cancel
                    </button>
                </div>
                </div>
            </div>
            </div>
        ) : null}
        </>
    );
    };

    export default Sidebar;
