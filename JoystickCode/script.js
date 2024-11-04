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
