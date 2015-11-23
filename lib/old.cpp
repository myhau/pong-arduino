//
// Created by mihau on 11/10/15.
//


MyTv TV(width, height);


bool powerToTheBall(int paddle){
    if(paddle==1){
        return ((y11 > 0 && py > 0) || (y11 <= 0 && py <= 0));
    }else{
        return ((y2 > 0 && py >0)||(y2<=0 && py <= 0));
    }
}

int random(int from, int to) {
    return 1;
}

void drawBall() {

    if(px + 6 >= width) {
        start = random(0,1);
        if(start==0){
            velocityPx = -1;
            velocityPy = 0;
        }else{
            velocityPx = 1;
            velocityPy = 0;
        }
        player1Score++;
        px = (width/2);
        py = (height/2);
    }

    if(px - 5 <= 1){
        if(start==0){
            velocityPx = -1;
            velocityPy = 0;
        }else{
            velocityPx = 1;
            velocityPy = 0;
        }
        player2Score++;
        px = (width/2);
        py = (height/2);
    }

    if(py + 6 >= height) velocityPy = -1;
    if(py - 5 <= 1) velocityPy = 1;

    if((px + 5  >= width -10) && (y11 >= py && y11 <= py + 30)){
        velocityPx = -velocityPx;
        if(powerToTheBall(2)){
            velocityPy += 0.1;
        }else{
            velocityPy -= 0.1;
        }
    }

    if((px - 5  <= 0) && (y11 >= py && y11 <= py + 30)){
        velocityPx = -velocityPx;
        if(powerToTheBall(1)){
            velocityPy += 0.1;
        }else{
            velocityPy -= 0.1;
        }
    }
    TV.draw_circle(px, py, 5, WHITE,INVERT);
}


void drawBoard() {
    TV.draw_rect(0, 0, width - 1, height - 1, WHITE);
}


void drawPaddle1(int y1) {
    if(y1 + 30 >= height) velocityY1 = -1;
    if(y1 <= 0) velocityY1 = 1;
    TV.draw_rect(0, y1, 10, 30,WHITE, INVERT);
}

void drawPaddle2(int y1) {
    if (y2 + 30 >= height) velocityY2 = -1;
    if (y2 <= 0) velocityY2 = 1;
    TV.draw_rect(width - 10, y1, 10, 30, WHITE, INVERT);

}

void delay(uint8_t mili) {
    sf::sleep(sf::milliseconds(mili));
}

void draw_pong() {
    y11 += velocityY1;
    y2 += velocityY2;

    px += velocityPx;
    py += velocityPy;


    drawPaddle1(y11);
    drawPaddle2(y2);
    drawBall();

    delay(1);
}


void start_game() {
    TV.delay_frame(1);
    TV.clear_screen();
    drawBoard();
    draw_pong();
}