import React, { useState } from 'react';

const Modal = ({ isOpen, onClose, title, children }) => {
  const handleModalClick = (event) => {
    // Evitar que el clic dentro del contenido del modal se propague al contenedor y lo cierre
    event.stopPropagation();
  };

  if (!isOpen) {
    return null;
  }

  return (
    <div
      className={`fixed z-50 inset-0 overflow-y-auto ${
        isOpen ? 'block' : 'hidden'
      }`}
      onClick={onClose}
    >
      <div className="flex items-center justify-center min-h-screen p-4">
        <div
          className="bg-white rounded-lg p-6 w-96 z-50"
          onClick={handleModalClick}
        >
          <div className="flex justify-between items-center mb-4">
            <h2 className="text-xl font-semibold">{title}</h2>
            <button
              className="text-gray-500 hover:text-gray-700"
              onClick={onClose}
            >
              X
            </button>
          </div>
          <div>{children}</div>
          <div className="mt-6 flex justify-end">
            <button className="mr-2 px-4 py-2 bg-blue-500 hover:bg-blue-600 text-white rounded-lg">
              Save
            </button>
            <button
              className="px-4 py-2 bg-gray-300 hover:bg-gray-400 text-gray-800 rounded-lg"
              onClick={()=>isOpen=false}
            >
              Cancel
            </button>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Modal;
