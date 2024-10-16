
//Outra maquina = alterar o IP
const URL = "http://10.0.2.240:3000/"

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

    for (let button of buttons) {

        let buttonValue = ++value;

        button.onmousedown = () => {
            console.log(`Botão ${buttonValue} pressionado`);
        };
        
        button.ontouchstart = button.onmousedown;
        
        button.onmouseup = () => {
            console.log(`Botão ${buttonValue} solto`);
        };
        
        button.ontouchend = button.onmouseup;
    };

    speed.onchange = () => {
        console.log(`Velocidade = ${speed.value}`);
    };

};

createControl();