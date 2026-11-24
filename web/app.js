let steps = [];
let cursor = 0;

const $ = (id) => document.getElementById(id);
const LETTERS = "abcdefghijklmnopqrstuvwxyz";

// Load the trace.json file produced by the C program.
$("loader").addEventListener("change", async (e) => {
  const text = await e.target.files[0].text();
  steps = JSON.parse(text);
  cursor = 0;
  $("timeline").max = steps.length - 1;
  render();
});

function render() {
  if (steps.length === 0) return;
  const s = steps[cursor];

  $("timeline").value = cursor;
  $("step-label").textContent = `Step ${cursor + 1} / ${steps.length}`;
  $("stack").innerHTML = s.stack.map((v) => `<li>${v}</li>`).join("");
  $("vars").innerHTML = s.vars
    .map((v, i) => (v !== 0 ? `<li>${LETTERS[i]} = ${v}</li>` : ""))
    .join("");
}

function go(delta) {
  cursor = Math.min(Math.max(cursor + delta, 0), steps.length - 1);
  render();
}

$("back").addEventListener("click", () => go(-1));
$("forward").addEventListener("click", () => go(1));
$("timeline").addEventListener("input", (e) => {
  cursor = Number(e.target.value);
  render();
});

// Walk backward from the current step to find the last time a variable changed.
$("find").addEventListener("click", () => {
  const idx = LETTERS.indexOf($("var-name").value.trim());
  if (idx < 0) { $("find-result").textContent = "Enter a letter a–z."; return; }

  for (let i = cursor; i > 0; i--) {
    if (steps[i].vars[idx] !== steps[i - 1].vars[idx]) {
      cursor = i;
      render();
      $("find-result").textContent = `Changed at step ${i + 1}, now ${steps[i].vars[idx]}.`;
      return;
    }
  }
  $("find-result").textContent = "No change found before this step.";
});

document.addEventListener("keydown", (e) => {
  if (e.key === "ArrowLeft") go(-1);
  if (e.key === "ArrowRight") go(1);
});