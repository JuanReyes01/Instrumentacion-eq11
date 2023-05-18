import React, { useEffect, useRef } from "react";
import Chart from "chart.js/auto";

function Graph({ title, data, labels, color }) {
  const chartRef = useRef(null);

  useEffect(() => {
    const canvas = chartRef.current;
    const ctx = canvas.getContext("2d");

    let chartInstance = null;

    if (chartRef.current) {
      // If chart instance exists, destroy it before creating a new chart
      if (chartRef.current.chartInstance) {
        chartRef.current.chartInstance.destroy();
      }

      chartInstance = new Chart(ctx, {
        type: "line",
        data: {
          labels: labels, // Use numeric labels for x-axis
          datasets: [
            {
              label: title,
              data: data,
              borderColor: color,
              backgroundColor: "rgba(75, 192, 192, 0.2)",
            },
          ],
        },
        options: {
          maintainAspectRatio: false,
          responsive: true,
          scales: {
            x: {
              type: "linear", // Use linear scale for x-axis
              display: true,
            },
            y: {
              type: "linear", // Use linear scale for y-axis
              display: true,
            },
          },
        },
      });

      chartRef.current.chartInstance = chartInstance;
    }

    return () => {
      // Cleanup function to destroy the chart instance
      if (chartInstance) {
        chartInstance.destroy();
      }
    };
  }, []);

  return (
    <div className="w-11/12 mx-auto mt-10">
      <canvas ref={chartRef} id="chart" className="h-55" />
    </div>
  );
}

export default Graph;
