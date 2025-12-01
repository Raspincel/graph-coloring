const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

let nodes = {};
let edges = [];
let draggingNode = null;
let hoveredNode = null;
let offsetX = 0;
let offsetY = 0;

function addNode() {
  const id = document.getElementById("nodeId").value.trim();
  const x = parseInt(document.getElementById("nodeX").value);
  const y = parseInt(document.getElementById("nodeY").value);
  const color = document.getElementById("nodeColor").value;

  if (!id) {
    alert("Please enter a node ID");
    return;
  }

  if (nodes[id]) {
    alert("Node already exists! Use a different ID.");
    return;
  }

  nodes[id] = { x, y, color, radius: 30 };

  draw();

  document.getElementById("nodeId").value = "";
}

function addEdge() {
  const from = document.getElementById("edgeFrom").value.trim();
  const to = document.getElementById("edgeTo").value.trim();

  if (!from || !to) {
    alert("Please enter both node IDs");
    return;
  }

  if (!nodes[from] || !nodes[to]) {
    alert("One or both nodes do not exist");
    return;
  }

  edges.push([from, to]);
  edges = removeRedundantEdges(edges);
  nodes = setColors(nodes, edges);

  draw();

  document.getElementById("edgeFrom").value = "";
  document.getElementById("edgeTo").value = "";
}

function clearGraph() {
  if (Object.keys(nodes).length === 0 && edges.length === 0) return;

  if (confirm("Clear all nodes and edges?")) {
    nodes = {};
    edges = [];
    draw();
  }
}

function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  // Draw edges
  edges.forEach((edge) => {
    const nodesArray = Object.entries(nodes);
    const node1 = nodesArray.find((n) => edge[0] == n[0])?.[1];
    const node2 = nodesArray.find((n) => edge[1] == n[0])?.[1];
    if (!node1 || !node2) return;

    ctx.beginPath();
    ctx.moveTo(node1.x, node1.y);
    ctx.lineTo(node2.x, node2.y);
    ctx.strokeStyle = "#cbd5e0";
    ctx.lineWidth = 3;
    ctx.stroke();
  });

  // Draw nodes
  Object.keys(nodes).forEach((id) => {
    const node = nodes[id];
    const isHovered = hoveredNode === id;
    const radius = isHovered ? node.radius * 1.2 : node.radius;

    // Shadow for hover effect
    if (isHovered) {
      ctx.shadowColor = node.color;
      ctx.shadowBlur = 20;
    }

    // Draw node circle
    ctx.beginPath();
    ctx.arc(node.x, node.y, radius, 0, Math.PI * 2);
    ctx.fillStyle = node.color;
    ctx.fill();
    ctx.strokeStyle = "white";
    ctx.lineWidth = 4;
    ctx.stroke();

    ctx.shadowBlur = 0;

    // Draw node label
    ctx.fillStyle = "white";
    ctx.font = "bold 14px Arial";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText(id, node.x, node.y);
  });
}

function getNodeAt(x, y) {
  for (let id in nodes) {
    const node = nodes[id];
    const dx = x - node.x;
    const dy = y - node.y;
    if (dx * dx + dy * dy <= node.radius * node.radius) {
      return id;
    }
  }
  return null;
}

// Initial example graph
nodes = {
  A: { x: 200, y: 150, color: "#667eea", radius: 30 },
  B: { x: 400, y: 150, color: "#4facfe", radius: 30 },
  C: { x: 400, y: 350, color: "#43e97b", radius: 30 },
  D: { x: 300, y: 400, color: "#fa709a", radius: 30 },
  E: { x: 150, y: 350, color: "#ff6b6b", radius: 30 },
};

edges = removeRedundantEdges([
  ["A", "B"],
  ["A", "C"],
  ["A", "D"],
  ["B", "C"],
  ["B", "E"],
  ["C", "E"],
]);

nodes = setColors(nodes, edges);

draw();
