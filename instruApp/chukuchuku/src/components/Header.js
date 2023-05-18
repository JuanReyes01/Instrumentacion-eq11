    import React, { useState } from "react";
    import Sidebar from "./Sidebar";

    const Header = (props) => {
    const [showSidebar, setShowSidebar] = useState(false);

    const handleSidebar = () => {
        setShowSidebar(!showSidebar);
    };

    return (
        <div>
        <div className="bg-blue-500 h-16 flex justify-between items-center px-4 text-white">
        <h1 className="text-2xl font-bold text-left">InstruApp</h1>
        </div>
        <Sidebar weight = {props.weight}/>
        </div>
    );
    };

    export default Header;
