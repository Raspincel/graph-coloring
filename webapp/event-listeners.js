canvas.addEventListener("mousedown", (e) => {
  const rect = canvas.getBoundingClientRect();
  const x = e.clientX - rect.left;
  const y = e.clientY - rect.top;

  const nodeId = getNodeAt(x, y);
  if (nodeId) {
    draggingNode = nodeId;
    offsetX = x - nodes[nodeId].x;
    offsetY = y - nodes[nodeId].y;
    canvas.style.cursor = "grabbing";
  }
});

canvas.addEventListener("mousemove", (e) => {
  const rect = canvas.getBoundingClientRect();
  const x = e.clientX - rect.left;
  const y = e.clientY - rect.top;

  if (draggingNode) {
    nodes[draggingNode].x = x - offsetX;
    nodes[draggingNode].y = y - offsetY;
    draw();
  } else {
    const nodeId = getNodeAt(x, y);
    if (nodeId !== hoveredNode) {
      hoveredNode = nodeId;
      canvas.style.cursor = nodeId ? "grab" : "default";
      draw();
    }
  }
});

canvas.addEventListener("mouseup", () => {
  draggingNode = null;
  canvas.style.cursor = hoveredNode ? "grab" : "default";
});

canvas.addEventListener("mouseleave", () => {
  draggingNode = null;
  hoveredNode = null;
  canvas.style.cursor = "default";
  draw();
});
