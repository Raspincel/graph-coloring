function removeRedundantEdges(edges) {
  const newEdges = {};
  const oldEdges = edges.slice();

  oldEdges.forEach((value) => {
    value.sort();

    const previousValues = newEdges[value[0]] ?? [];
    if (previousValues.includes(value[1])) {
      return;
    }

    const newValue = [...previousValues, value[1]];
    newEdges[value[0]] = newValue;
  });

  return Object.entries(newEdges).flatMap((value) => {
    return value[1].map((node) => [value[0], node]);
  });
}

function setColors(nodes, edges) {
  const tree = createTree(edges);
  const colors = selectColors(nodes, tree);

  Object.entries(colors).forEach((v) => {
    nodes[v[0]].color = v[1][0];
  });

  return nodes;
}

function createTree(edges) {
  const traverse = (nodeId) => {
    const edgesWithNode = edges.filter((value) => value[0] === nodeId);

    if (edgesWithNode.length === 0) return { [nodeId]: {} };

    let obj = {};

    edgesWithNode.forEach((value) => {
      obj = { ...obj, ...traverse(value[1]) };
    });

    return { [nodeId]: obj };
  };

  return traverse(edges[0][0]);
}

function selectColors(n, tree) {
  const possibleColors = [
    "#667eea",
    "#f093fb",
    "#4facfe",
    "#43e97b",
    "#fa709a",
    "#feca57",
    "#ff6b6b",
    "#95afc0",
  ];

  const nodes = Object.keys(n);
  const colorsObject = {};

  nodes.forEach((v) => {
    colorsObject[v] = possibleColors.slice();
  });

  const traverse = (nodeId, branch) => {
    const color = colorsObject[nodeId][0];

    const nextIds = Object.keys(branch);

    for (let i = 0; i < nextIds.length; i++) {
      colorsObject[nextIds[i]] = colorsObject[nextIds[i]].filter(
        (v) => v !== color
      );
    }

    for (let i = 0; i < nextIds.length; i++) {
      traverse(nextIds[i], branch[nextIds[i]]);
    }
  };

  traverse("A", tree["A"]);

  return colorsObject;
}
