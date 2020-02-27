class Entity{
    constructor (x,y,img)
    {
    this.x = x;
    this.y = y;
    this.image = new Image();
    if(img)
        this.image.src = img;
    this.dead = false;
    this.scale = 1;
    this.FACE_LEFT = false;
    this.FACE_Right = true;
    }
    checkMarginsOverlap(obiect)
    {
        if(this.x <= obiect.x + obiect.image.width * obiect.scale &&
            this.x + this.image.width * this.scale >= obiect.x &&
            this.y <= obiect.y + obiect.image.height * obiect.scale &&
            this.y + this.image.height * this.scale >= obiect.y)
                return true;
        return false;
    }
    destroy()
    {  
        this.dead = true;
    }
    drawMe()
    {
        document.getElementById("gc").getContext("2d").drawImage(this.image,0,0,this.image.width,this.image.height,this.x,this.y,this.image.width*this.scale,this.image.height*this.scale);
    }
}

class Player extends Entity{
    constructor (x,y)
    {
    super(x,y);
    this.gravity = 4;
    this.speed = 3.5;
    this.falling = true;
    this.jumping = false;
    this.velocity = {x:0,y:0};
    this.bullets = [];
    }
    LeftCollision(obiect)
    {
        if(this.checkMarginsOverlap(obiect) && obiect.dead != true)
        {
            if(this.x >= obiect.x + obiect.image.width * obiect.scale + this.velocity.x - 2)
            {
                
                    return true;
            }
        }
        return false;
    }
    RightCollision(obiect)
    {
        if(this.checkMarginsOverlap(obiect) && obiect.dead != true)
        {
            if(this.x + this.image.width * this.scale <= obiect.x + this.velocity.x + 2)
               {
                    return true;
               }
        }
        return false;
    }
    TopCollision(obiect) // TOP OF PLAYER !!!!!!!
    {
        if(this.checkMarginsOverlap(obiect)&& obiect.dead != true)
        {
            if(this.y > obiect.y + obiect.image.height * obiect.scale + this.velocity.y+2)
            {
                console.log("ph")
                return true;
            }
        }
        return false;
    }
    BottomCollision(obiect) // BOTTOM OF PLAYER !!!!!!!!
    {
        if(this.checkMarginsOverlap(obiect) && obiect.dead != true){
            if(this.y + this.image.height * this.scale < obiect.y + this.velocity.y+2)
            {
                return true;
            }
        }   
        return false;
    }
    Animate()
    {  
        if(this.dead)
        {

        }
        else
        if(this.jumping || this.falling)
        {
            this.image.src = "imagini/player/jump.gif";

        }
        else{
            this.image.src = "imagini/player/stand.png";
        }
    }
    destroy()
    {  
        this.dead = true;
    }
    impusca()
    {
        if(this.FACE_RIGHT)
            this.bullets.push(new Bullet(this.x + this.image.width * this.scale,
                                         this.y + this.image.height * this.scale/2,
                                         this));
        else
            this.bullets.push(new Bullet(this.x,
                                         this.y + this.image.height * this.scale/2,
                                         this))

    }
    drawMe()
    {
        var ctx = document.getElementById("gc").getContext("2d");

        if(this.FACE_LEFT){
            ctx.scale(-1, 1);                      // flip hor.
            ctx.drawImage(this.image,0,0,
                        this.image.width,this.image.height,
                        -this.x - (this.scale)*this.image.width, this.y,
                        this.image.width * this.scale, this.image.height * this.scale); // aici se da flip la context, se deseneaza imagine 
            ctx.scale(-1, 1);                                                                          // in forma ei originala si se da flip inapoi, desenandu-se "pe dos" imaginea
        }

        else{
            ctx.drawImage(this.image, 0, 0, 
                        this.image.width ,this.image.height,
                        this.x, this.y,
                        this.image.width * this.scale,  this.image.height * this.scale); 
        }
    }
}

class Crosshair {
    constructor() {
        this.image = new Image();
        this.image.src = "imagini/crosshair046.png";
        this.scale = 1;
    }
    drawMe(){
        document.getElementById("gc").getContext("2d").drawImage(this.image,0,0,
            this.image.width, this.image.height,
            mouseX - this.image.width * this.scale / 2,    mouseY - this.image.height * this.scale / 2,
            this.image.width * this.scale,    this.image.height * this.scale);
    }
}

class Bullet{ // din dreapta player-ului la mijloc, spawnez un glont. glontul initial e la x,y catre x1,y1, il rotesc cu sinus //ctx.fillRect(x, y, w,h);
    constructor(x,y,cineTrage){
        this.x = x;
        this.y = y;
        this.cineTrage = cineTrage;
        this.speed = 40;
        this.size = 0.8 ;
        this.dead = false;
        this.angle = (Math.atan2(mouseY - this.y - 20,mouseX - this.x + 2)/Math.PI*180);
        this.velocity = {
            x: Math.cos(this.angle/180*Math.PI)*this.speed,
            y: Math.sin(this.angle/180*Math.PI)*this.speed
        }
        sound.push(new Sunet("sunete/piu.m4a",0.2));

        }
    omoara(){
        for(x of AllPlayers)
            if(this.checkMarginsOverlap(x) &&
               this.cineTrage != x &&
                this.dead == false &&
                x.dead == false)
                {
                    x.destroy();
                    this.destroy();
                }
        for(let i=1;i < obstacole.length;i++)
            if(this.checkMarginsOverlap(obstacole[i]))
            {
                this.destroy();
            }
    }
    destroy()
    {  
        this.dead = true;
    }
    Update()
    {   
        if(this.dead == false)
        {
            this.omoara();
            this.x = this.x + this.velocity.x;
            this.y = this.y + this.velocity.y;
        }
    }
    checkMarginsOverlap(obiect)
    {
        if(this.x + this.velocity.x <= obiect.x + obiect.image.width * obiect.scale &&
            this.x + this.velocity.x >= obiect.x &&
            this.y + this.velocity.y <= obiect.y + obiect.image.height * obiect.scale &&
            this.y + this.velocity.y >= obiect.y)
            {
                return true;}
        return false;
    }
}

class Sunet{
    constructor(src,volume){  
        this.sound = document.createElement("audio");
        this.sound.src = src;
        this.sound.setAttribute("preload", "auto");
        this.sound.setAttribute("controls", "none");
        this.sound.style.display = "none";  
        this.sound.volume = volume;
        this.play = function(){
            this.sound.play();
        }
        this.stop = function(){
            this.sound.pause();
        }
    }
}

class Obstacol extends Entity{
    constructor(x,y,img){
        super(x,y,img);
    }
    SetPosition(x,y){
        this.x = x;
        this.y = y;
    }
}


Entity.prototype.setScale = function(scale)
{
    this.scale = scale;
};

class Enemy extends Player{
    constructor(x,y)
    {
        super(x,y);
    }
    Animate()
    {
        if(this.dead)
        {
        }
        else
        if(this.jumping || this.falling)
        {
            this.image.src = "imagini/enemy/jump.gif";

        }
        else{
            this.image.src = "imagini/enemy/stand.png";
        }
    }
}

        ///// SPRITES AND CONTROLLER /////

var Jucator = new Player(300,0);
var Inamic = new Enemy(700,560);
var AllPlayers = [];
AllPlayers.push(Jucator);
AllPlayers.push(Inamic);

var crosshair = new Crosshair;
var bg = new Obstacol(0,0,"imagini/bg.png");
var podea = new Obstacol(0,0,"imagini/podea.png");
var controller = new Object();
        //////// SOUNDS ///////

sound = [new Sunet("sunete/piu.m4a",0.2)];
ftunks = [new Sunet("sunete/ftunk.m4a",0.02)];
Megalovania = new Sunet("sunete/Megalovania.mp3",0.01);
        ///// PHYSICS //////

var max_vx = 5;
var max_vy = 10;
var friction = 0.85;
        ///// MOUSE INPUT /////

var mouseX;
var mouseY;
        ////// KEYBOARD INPUT ///////

var A_KEY = 65;
var S_KEY = 83;
var D_KEY = 68;
var W_KEY = 87;


////////////////////////////////////
/////// KEYBOARD & MOUSE INPUT ////
//////////////////////////////////


document.onkeydown = function(e){
    toggleKey(e.keyCode, true);
}

document.onkeyup = function(e){
    toggleKey(e.keyCode, false);
}

function toggleKey(keyCode, isPressed){
    if(keyCode === A_KEY)
        controller.left = isPressed;
    if(keyCode === S_KEY)
        controller.down = isPressed;
    if(keyCode === D_KEY)
        controller.right = isPressed;
    if(keyCode === W_KEY)
        controller.up = isPressed;
    
}

//////////////////////////////////
////////// PLAYER MOVEMENT //////
///////////////////////////////


var StaPeObstacol = false;

function handleControls(){
/**
*   KEYBOARD
*/
    if(Jucator.falling)
        {
                    Jucator.velocity.y += Jucator.gravity;
                if(Jucator.velocity.y < Jucator.gravity * 3)
                    Jucator.velocity.y = Jucator.gravity * 3;
        }
    if(controller.up && Jucator.falling == false){ // cat timp apesi W si player-ul nu cade
            jumpHeight += 1;
            if(jumpHeight < max_vy) // cat timp jumpHeight e mai mic decat max_vy, player-ul inca sare
            {
                Jucator.falling = false;
                Jucator.jumping = true;
                Jucator.velocity.y -= 1.3*Jucator.gravity;
            }
            else    // dupa ce jumpHeight trece de max_vy, player-ul cade si jumpHeight incepe de la 0
            {   
                jumpHeight = 0;
                Jucator.falling = true;
                Jucator.jumping = false;
            }
    }
    else if(!controller.up && Jucator.jumping == true){   // daca iei degetul de pe W in timp ce sare
        jumpHeight = 0;
        Jucator.falling = true;
        Jucator.jumping = false;
    }
    if(controller.left){
                Jucator.velocity.x -= Jucator.speed;
                if(Jucator.velocity.x < -Jucator.speed * max_vx)
                    Jucator.velocity.x = -Jucator.speed * max_vx;
    }
    if(controller.right){
                Jucator.velocity.x += Jucator.speed;
                if(Jucator.velocity.x > Jucator.speed * max_vx)
                    Jucator.velocity.x = Jucator.speed * max_vx;
        }
    Jucator.velocity.x *= friction;

    let obstacoleSiPlayeri = [];

    for(let i=1;i<obstacole.length;i++)
        obstacoleSiPlayeri.push(obstacole[i]);
    for(x of AllPlayers)
        obstacoleSiPlayeri.push(x);

    for(obstacol of obstacoleSiPlayeri)
    {
        
        if(Jucator.TopCollision(obstacol) &&
        !Jucator.RightCollision(obstacol) &&
        !Jucator.LeftCollision(obstacol))
        {   
            Jucator.y = obstacol.y + obstacol.image.height * obstacol.scale;
            Jucator.velocity.y = 0;
            Jucator.jumping = false;
            Jucator.falling = true;
            
        }
        else 
        if(Jucator.BottomCollision(obstacol) &&
            !Jucator.RightCollision(obstacol) &&
            !Jucator.LeftCollision(obstacol))
            {
                    if(Jucator.falling){
                    ftunks.push(new Sunet("sunete/ftunk.m4a",0.2));
                }
                StaPeObstacol = true;
                Jucator.velocity.y = 0;
                Jucator.y = obstacol.y - Jucator.image.height * Jucator.scale;
                Jucator.jumping = false;
                Jucator.falling = false;
            }
        if(Jucator.LeftCollision(obstacol))
        {
            if(Jucator.velocity.x < 0)
            {
                Jucator.x = obstacol.x + obstacol.image.width * obstacol.scale;
                Jucator.velocity.x = 0;
            }
        }
        else if(Jucator.RightCollision(obstacol))
        {
            if(Jucator.velocity.x > 0)
            {
                Jucator.x = obstacol.x - Jucator.image.width * Jucator.scale;
                Jucator.velocity.x = 0;
            }
        }
        
        
    }
    if(StaPeObstacol == false && Jucator.jumping == false)
    {
            Jucator.falling = true;
    }
    StaPeObstacol = false;
    Jucator.y += Jucator.velocity.y;
    if(!Jucator.LeftCollision(obstacol) && !Jucator.RightCollision(obstacol))
        Jucator.x += Jucator.velocity.x;
        
/**
*   MOUSE
*/
    if(mouseX < Jucator.x + Jucator.image.width * Jucator.scale / 2)
    {
        Jucator.FACE_LEFT = true;
        Jucator.FACE_RIGHT = false;
    }
    else
    {
        Jucator.FACE_LEFT = false;
        Jucator.FACE_RIGHT = true;
    }
    
}


////////////////////////////////////
////// RECURSIVE DRAW FUNCTION ////
//////////////////////////////////


function draw(){ 
    ctx.drawImage(bg.image,0,0,bg.image.width,bg.image.height,0,0,canvas.width,canvas.height);
    
    
    for(let i = 1; i < obstacole.length; i++)
        obstacole[i].drawMe();
    for(let i = 0; i < AllPlayers.length; i++)
        if(AllPlayers[i].dead == false)
            AllPlayers[i].drawMe();

    ///////////    DIRECTIA IN CARE SE UITA JUCATORUL   /////////
    for(cineTrage of AllPlayers)
        for(bullet of cineTrage.bullets)
            {
                if(bullet.dead == false)
                {
                    ctx.beginPath();
                    ctx.lineWidth = 2;
                    ctx.strokeStyle = "#7FFFD4";
                    ctx.moveTo(bullet.x,bullet.y);
                    ctx.lineTo(bullet.x + bullet.velocity.x * bullet.size,bullet.y + bullet.velocity.y * bullet.size);
                    ctx.stroke();
                    ctx.closePath();
                }
            }


    if(Jucator.dead == false){

    }

    if(mouseX && mouseY){
        crosshair.drawMe();
    }
}


function loop()
{

    /////////////           COLLISIONS                 /////////////////

if(Jucator.dead == false){
    

    for (let i = ftunks.length-1; i>0; i--)
    {
        if(ftunks[i]!=null)
            ftunks[i].play();
        ftunks[i] = null;
    }
    
    for(let i = sound.length-1;i>0;i--)
    {
        if(sound[i]!=null)
            sound[i].play();
        sound[i] = null;
    }
    
    if(Jucator.x <= 0)
        Jucator.x = 0;
    if(Jucator.x >= canvas.width - Jucator.image.width * Jucator.scale)
    {
        Jucator.x = canvas.width - Jucator.image.width * Jucator.scale;
    }

    if(Jucator.y <= -10)
    {
        Jucator.y = -10;
    }


        handleControls(); // functie care ia input-ul si schimba pozitiile player-ului
}

for(x of AllPlayers)
    if(x.dead == false){
        for(bullet of x.bullets)
        {
            if(bullet != null)
                bullet.Update();
        }
        x.Animate();

    }

    draw();
    requestAnimationFrame(loop);
}

//////////////////////////////
//////     START GAME   /////
////////////////////////////


function StartGame(){
    canvas = document.getElementById("gc");
    ctx = canvas.getContext("2d");
    ctx.imageSmoothingEnabled = false;
    podea.setScale(2);
    podea.SetPosition(0,canvas.height - podea.image.height * podea.scale);

    obstacole = [];
    obstacole.push(bg);
    obstacole.push(podea);
    obstacole.push(new Obstacol(400,250,"imagini/platforma02.png"));
    obstacole.push(new Obstacol(150,400,"imagini/platforma01.png"));
    obstacole.push(new Obstacol(350,500,"imagini/platforma01.png"));
    obstacole.push(new Obstacol(550,500,"imagini/platforma01.png"));
    obstacole.push(new Obstacol(750,400,"imagini/platforma01.png"));

    Jucator.setScale(6);
    Inamic.setScale(6);
    
    for(let i=2;i < obstacole.length;i++)
        obstacole[i].setScale(2);

    jumpHeight = 0;
    Megalovania.play();

    canvas.onmousemove = function(e){
        mouseX = e.offsetX;
        mouseY = e.offsetY;
    }
    canvas.onclick = function(){
        if(Jucator != null && Jucator.dead == false)
            Jucator.impusca();
    }

    loop();    
}

var start = true;

    window.onload = function()
    {
        window.onclick = function()
        {
            if(start)
                StartGame();
            start = false;
        }
    }

