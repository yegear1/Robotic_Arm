const char* indexHTML = R"HTML(
  <!DOCTYPE html>
  <html lang="pt-br">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      
      <style>
          * {
                  margin: 0;
                  padding: 0;
                  box-sizing: border-box;
                  font-family: Arial, Helvetica, sans-serif;
              }

              body{
                  background: #000;
                  color: #fff;

                  height: 100vh;

                  flex-direction: column;
              }

              header{
                  display: grid;
                  grid-template-columns: 25vw 10vw 10vw 10vw 10vw 35vw;
                  grid-template-rows: 6vw;
                  margin-bottom: 2vw;
              }

              header .button{
                  width: 5vw;
                  height: 3vw;
                  border-radius: 1vw;
                  font-size: 1.5vw;

                  color: #000;
                  background: #fff;
              }

              main {
                  display: grid;
                  grid-template-columns: 30vw 30vw 40vw;
                  grid-auto-rows: 30vw;
              }

              .row3 {
                  display: grid;
                  grid-template-rows: 10vw 10vw 10vw;

                  
              }

              .center {
                  display: flex;
                  justify-content: center;
                  align-items: center;

                  
              }

              .column3 {
                  display: grid;
                  grid-template-columns: 10vw 10vw 10vw;
                  
              
              }

              .colum5{
                  display: grid;
                  grid-template-columns: 10vw 5vw 10vw 5vw 10vw;
              }

              .directional{
                  background: #fff;
                  border-radius: 15vw;

              }

              .directional button{
                  background: none;
                  border: none;
                  font-size: 3vw;
              }

              button{
                  user-select: none;
                  -webkit-touch-callout: none;
                  -webkit-user-select: none;
                  -moz-user-select: none;

                  appearance: none;
                  -webkit-appearance: none;

                  cursor: pointer;
              }

              .slider{
                  transform: rotate(90deg);

                  appearance: none;
                  -webkit-appearance: none;

                  width: 20vw;
                  height: 6vw;
                  border-radius: 3vw;

                  outline: none;
                  background: #fff;
              }

              .slider::-webkit-slider-thumb{
                  appearance: none;
                  -webkit-appearance: none;

                  width: 6vw;
                  height: 6vw;
                  border-radius: 3vw;

                  background: #707070;
                  cursor: pointer;
              }

              .slider::-moz-range-thumb{

                  width: 6vw;
                  height: 6vw;
                  border-radius: 3vw;

                  background: #707070;
                  cursor: pointer;
              }

              .buttons button{
                  font-size: 4vw;
                  border-radius: 5vw;
              }
      </style>

      <title>Joystick</title>
  </head>
  <body class="center">
      
      <header>
          <div></div>

          <div class="center">
              <div id="screenButton" class="button center">&#9974;</div>
          </div>
          
          <div class="center">
              <button id="key_1" class="button">&#9654;</button>
          </div>

          <div class="center">
              <button id="key_2" class="button">&#9679;</button>
          </div>

          <div class="center">
              <button id="key_3" class="button">x</button>
          </div>

          <div></div>
      </header>

      <main>
          <section class="directional row3">
              <div class="column3">
                  <div></div>

                  <button id="key_w">&#9650;</button>

                  <div></div>
              </div>

              <div class="column3">
                  <button id="key_a">&#9664;</button>

                  <div></div>

                  <button id="key_d">&#9654;</button>
              </div>

              <div class="column3">
                  <div class=""></div>

                  <button id="key_s">&#9660;</button>

                  <div class=""></div>
              </div>
          </section>

          <section class="center">
              <input
                  type="range"
                  min="1"
                  max="25"
                  class="slider"
                  id="speed"
              >
          </section>

          <section class="buttons row3">
              <div class="colum5">
                  <button id="key_i">S</button>

                  <div></div>

                  <button id="key_7">G+</button>

                  <div></div>
                  
                  <button id="key_5">&#9650;</button>
              </div>

              <div></div>

              <div class="colum5">
                  <button id="key_k">D</button>

                  <div></div>

                  <button id="key_8">G-</button>

                  <div></div>
                  
                  <button id="key_6">&#9660;</button>
              </div>
          </section>
      </main>

      <script>
          const URL = "./";

          async function sendRequest(value, response) {
              try {
                  await fetch(`${URL}${value}`, {
                      mode: 'no-cors',
                  });
              
                  await response();
              } catch {
                  alert("Servidor Desligado")
              }
          };


          function toggleFullScreen(){
              if(document.fullscreenEnabled){
                  if(document.fullscreenElement) {
                      document.exitFullscreen();
                      return;
                  }

                  document.documentElement.requestFullscreen();
              }
          }


          function createControl() {

              screenButton.onmousedown = toggleFullScreen;
              screenButton.ontouchend = screenButton.onmousedown;

              const buttons = document.getElementsByTagName('button');

              let up = false;

              let keys = new Object();

              let keyPress = false;

              let speedControl = 12;

              document.onkeydown = (event) => {
                  if(keys[`key_${event.key}`]) {
                      if(!keyPress){
                          keys[`key_${event.key}`]();
                      };
                  };
              };

              document.onkeyup = (event) => {
                  if(keys[`key_${event.key}_up`]) {
                      keys[`key_${event.key}_up`]();
                      keyPress=false;
                  };
              };

              for (let button of buttons) {

                  button.onmousedown = () => {
                  
                      sendRequest(`button=${button.id}`, () => {
                          if(up)sendRequest(`button=0`, () => {});
                      });

                      up = false;
                  };
                  
                  button.ontouchstart = button.onmousedown;
                  
                  button.onmouseup = () => {

                      keyPress=true;
                      
                      up = true

                      sendRequest(`button=0`, () => {})
                  };
                  
                  button.ontouchend = button.onmouseup;

                  keys[button.id] = button.onmousedown;
                  keys[`${button.id}_up`] = button.onmouseup
              };

              speed.onmouseup = () => {
                  sendRequest(`speed/${speed.value}`, () => {});
              };

              speed.ontouchend = speed.onmouseup;

              keys[`key_ArrowDown`] = () => {
                  if (speedControl <= speed.max){
                      speed.value = ++speedControl;
                  };
              };

              keys[`key_ArrowUp`] = () => {
                  if(speedControl >= speed.min){
                      speed.value = --speedControl;
                  };
              };

              keys[`key_ArrowDown_up`] = speed.onmouseup;
              keys[`key_ArrowUp_up`] = speed.onmouseup;

          };

          createControl();

      </script>
  </body>
  </html>
)HTML";