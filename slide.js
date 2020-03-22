let open = false;
let slider = document.getElementById('slider');
let icon = document.querySelector('#icon i');
let classOpen = 'fa-angle-double-up';
let classDown = 'fa-angle-double-down';

//slider.style.marginTop = '-1000px';
//slider.style.display = 'none';
slider.style.marginTop =  '-'+slider.clientHeight+'px';
icon.addEventListener('click',()=>{
    if(open){
            icon.classList.remove(classOpen)
            icon.classList.add(classDown);
            //console.log(slider)
            slider.style.marginTop =  '-'+slider.clientHeight+'px';
             //slider.style.display = 'none';
            
       
    }else{
        icon.classList.add(classOpen)
        icon.classList.remove(classDown);
        //slider.style.display = 'block';
        
       slider.style.marginTop = '0px';
    }
    open = !open;
})

let text = "";
let input = document.getElementById('input');
let button = document.getElementById('submit');

button.addEventListener('click',()=>{
  //  if(text.length > 0) window.location.reload();
    icon.classList.remove(classOpen)
    icon.classList.add(classDown);
    //console.log(slider)
    slider.style.marginTop =  '-'+slider.clientHeight+'px';
    text = input.value;
    console.log(text);
    encodeHuffman(text);

})