const WebSocketServer = require('ws');
const express = require('express');

const wss = new WebSocketServer.Server({ port: 14100 });
const app = express();

// Array to store all connected clients
const clients = [];

wss.on("connection", ws => {
    console.log("New client connected");

    // Add the new client to the array
    clients.push(ws);

    // Sending a welcome message to the new client
    ws.send('Welcome, you are connected!');

    ws.on("message", data => {
        console.log(`Client has sent us: ${data}`);

        // Broadcast the message to all connected clients
        clients.forEach(client => {
            if (client !== ws && client.readyState === WebSocketServer.OPEN) {
                client.send(`${data}`);
            }
        });
    });

    ws.on("close", () => {
        console.log("Client disconnected");

        // Remove the disconnected client from the array
        clients.splice(clients.indexOf(ws), 1);
    });

    ws.onerror = function () {
        console.log("Some error occurred");
    };
});

console.log("The WebSocket server is running on port 50");



app.get('/client',(req,res)=>res.sendFile(path.resolve(__dirname, './client .html')));
// app.listen(HTTP_PORT, ()=> console.log(`HTTP server listening at ${HTTP_PORT}`));









