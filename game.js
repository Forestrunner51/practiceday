const canvas = document.getElementById("game");
const ctx = canvas.getContext("2d");

const keys = {};
window.addEventListener("keydown", (e) => (keys[e.key.toLowerCase()] = true));
window.addEventListener("keyup", (e) => (keys[e.key.toLowerCase()] = false));

const player = { x: 400, y: 300, r: 14, speed: 220, color: "#89b4fa" };
let coins = [];
let enemies = [];
let score = 0;
let gameOver = false;

function rand(min, max) {
  return Math.random() * (max - min) + min;
}

function spawnCoin() {
  coins.push({ x: rand(20, canvas.width - 20), y: rand(20, canvas.height - 20), r: 8 });
}

function spawnEnemy() {
  // Spawn on a random edge so enemies don't appear on top of the player
  const side = Math.floor(Math.random() * 4);
  const x = side === 0 ? 0 : side === 1 ? canvas.width : rand(0, canvas.width);
  const y = side === 2 ? 0 : side === 3 ? canvas.height : rand(0, canvas.height);
  enemies.push({ x, y, r: 12, speed: rand(60, 110) });
}

function reset() {
  player.x = canvas.width / 2;
  player.y = canvas.height / 2;
  coins = [];
  enemies = [];
  score = 0;
  gameOver = false;
  for (let i = 0; i < 5; i++) spawnCoin();
  for (let i = 0; i < 2; i++) spawnEnemy();
}

function circlesTouch(a, b) {
  return Math.hypot(a.x - b.x, a.y - b.y) < a.r + b.r;
}

function update(dt) {
  if (gameOver) {
    if (keys["enter"]) reset();
    return;
  }

  let dx = 0;
  let dy = 0;
  if (keys["w"] || keys["arrowup"]) dy -= 1;
  if (keys["s"] || keys["arrowdown"]) dy += 1;
  if (keys["a"] || keys["arrowleft"]) dx -= 1;
  if (keys["d"] || keys["arrowright"]) dx += 1;

  // Normalize so diagonal movement isn't faster
  const len = Math.hypot(dx, dy);
  if (len > 0) {
    player.x += (dx / len) * player.speed * dt;
    player.y += (dy / len) * player.speed * dt;
  }
  player.x = Math.max(player.r, Math.min(canvas.width - player.r, player.x));
  player.y = Math.max(player.r, Math.min(canvas.height - player.r, player.y));

  for (const e of enemies) {
    const angle = Math.atan2(player.y - e.y, player.x - e.x);
    e.x += Math.cos(angle) * e.speed * dt;
    e.y += Math.sin(angle) * e.speed * dt;
    if (circlesTouch(player, e)) gameOver = true;
  }

  coins = coins.filter((c) => {
    if (circlesTouch(player, c)) {
      score++;
      if (score % 5 === 0) spawnEnemy();
      return false;
    }
    return true;
  });
  while (coins.length < 5) spawnCoin();
}

function drawCircle(obj, color) {
  ctx.fillStyle = color;
  ctx.beginPath();
  ctx.arc(obj.x, obj.y, obj.r, 0, Math.PI * 2);
  ctx.fill();
}

function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  coins.forEach((c) => drawCircle(c, "#f9e2af"));
  enemies.forEach((e) => drawCircle(e, "#f38ba8"));
  drawCircle(player, player.color);

  ctx.fillStyle = "#fff";
  ctx.font = "20px system-ui";
  ctx.textAlign = "left";
  ctx.fillText(`Score: ${score}`, 12, 28);

  if (gameOver) {
    ctx.fillStyle = "rgba(0, 0, 0, 0.6)";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = "#fff";
    ctx.textAlign = "center";
    ctx.font = "40px system-ui";
    ctx.fillText("Game Over", canvas.width / 2, canvas.height / 2 - 10);
    ctx.font = "20px system-ui";
    ctx.fillText("Press Enter to restart", canvas.width / 2, canvas.height / 2 + 25);
  }
}

let last = performance.now();
function loop(now) {
  const dt = Math.min((now - last) / 1000, 0.05);
  last = now;
  update(dt);
  draw();
  requestAnimationFrame(loop);
}

reset();
requestAnimationFrame(loop);
