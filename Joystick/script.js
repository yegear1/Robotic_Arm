
const URL = "http://127.0.1.1:3000/";

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

    let value = 0;

    let up = false;

    for (let button of buttons) {

        let buttonValue = ++value;

        button.onmousedown = () => {
            console.log(`Botão ${buttonValue} pressionado`);
        
            sendRequest(`button=${buttonValue}`, () => {
                if(up)sendRequest(`button=0`, () => {});
            });

            up = false;
        };
        
        button.ontouchstart = button.onmousedown;
        
        button.onmouseup = () => {
            console.log(`Botão ${buttonValue} solto`);
            
            up = true

            sendRequest(`button=0`, () => {})
        };
        
        button.ontouchend = button.onmouseup;
    };

    speed.onchange = () => {
        console.log(`Velocidade = ${speed.value}`);
    };

};

createControl();