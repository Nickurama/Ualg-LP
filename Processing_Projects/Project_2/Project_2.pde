final color BLACK = color(0, 0, 0);
final private boolean DEBUG_MODE = true;

//Playspace Config
final int BUBBLE_SIZE = 50;
final int PADDING = 20;
final int WIDTH_BUBBLES = 10;
final int HEIGHT_BUBBLES = 18; //effective space for bubbles: HEIGHT_BUBBLES - CANNON_SPACE_BUBBLES
final int MAX_BUBBLES = 10;
final int CANNON_SPACE_BUBBLES = 3;
final float COLLISION_OFFSET_MULTIPLIER = 0.9;

final color WALL_COLOR = color(255, 255, 0);
final color CEILINLG_COLOR = color(100, 100, 100);
final color CANON_COLOR = color(255, 255, 0);
final color PLAYSPACE_COLOR = color(255, 255, 255);

final float RELOAD_TIME = 0.5;

//calculation helpers
int windowWidth;
int windowHeight;

int nextBubbleDisplayX;
int nextBubbleDisplayY;
float cannonToNextBubbleDistX;
float cannonToNextBubbleDistY;

//vars
float timeElapsed;
float timeElapsedAnimation;
boolean isReloadingCannon;

//Playspace elements
Cannon cannon;
Ceiling ceiling;
Bubble nextBubble;
ArrayList<Bubble> bubbles;
BubbleGrid bubbleGrid;

void settings()
{
    windowWidth = BUBBLE_SIZE * WIDTH_BUBBLES + PADDING * 2;
    windowHeight = BUBBLE_SIZE * HEIGHT_BUBBLES + PADDING;
    size(windowWidth, windowHeight);
}

void setup()
{
    bubbleGrid = new BubbleGrid(PADDING, PADDING, HEIGHT_BUBBLES - CANNON_SPACE_BUBBLES, WIDTH_BUBBLES, BUBBLE_SIZE, PADDING);
    bubbles = new ArrayList<Bubble>();
    timeElapsed = 0;
    timeElapsedAnimation = 0;
    nextBubbleDisplayX = windowWidth / 2 - (2 * BUBBLE_SIZE);
    nextBubbleDisplayY = windowHeight - (1 * BUBBLE_SIZE);
    
    ceiling = new Ceiling(WALL_COLOR, CEILINLG_COLOR, BUBBLE_SIZE, WIDTH_BUBBLES, HEIGHT_BUBBLES, PADDING, MAX_BUBBLES);
    cannon = new Cannon(windowWidth / 2, windowHeight - (2 * BUBBLE_SIZE), BUBBLE_SIZE, CANON_COLOR);
    
    cannonToNextBubbleDistX = abs(nextBubbleDisplayX - cannon.getX());
    cannonToNextBubbleDistY = abs(nextBubbleDisplayY - cannon.getY());
    
    Bubble firstBubble = new Bubble(0, 0, BUBBLE_SIZE);
    bubbles.add(firstBubble);
    cannon.loadBubble(firstBubble);
    nextBubble = new Bubble(nextBubbleDisplayX, nextBubbleDisplayY, BUBBLE_SIZE);
    bubbles.add(nextBubble);
}

void reloadCannon(float deltaT)
{
    timeElapsedAnimation += deltaT;
    nextBubble.setX(nextBubble.getX() + cannonToNextBubbleDistX * deltaT / RELOAD_TIME);
    nextBubble.setY(nextBubble.getY() - cannonToNextBubbleDistY * deltaT / RELOAD_TIME);
    if (timeElapsedAnimation >= RELOAD_TIME)
    {
        nextBubble.setX(cannon.getX());
        nextBubble.setY(cannon.getY());
        cannon.loadBubble(nextBubble);
        isReloadingCannon = false;
        timeElapsedAnimation = 0;
        
        generateNextBubble();
    }
}

void generateNextBubble()
{
    nextBubble = new Bubble(nextBubbleDisplayX, nextBubbleDisplayY, BUBBLE_SIZE);
    bubbles.add(nextBubble);
}

void keyPressed()
{
    if (keyCode == LEFT || keyCode == 'A')
    {
        cannon.rotateLeft();
    }
    else if (keyCode == RIGHT || keyCode == 'D')
    {
        cannon.rotateRight();
    }
    else if (keyCode == ' ' || keyCode == UP || keyCode == 'W')
    {
        if (cannon.shoot())
        {
            isReloadingCannon = true;
        }
    }
}

void handleCollisions(Bubble b)
{
    if (b.getX() - BUBBLE_SIZE / 2 < PADDING) // left wall collision
        {
        b.setX(PADDING + BUBBLE_SIZE / 2);
        b.ricochet();
    }
    else if (b.getX() + BUBBLE_SIZE / 2 > windowWidth - PADDING) // right wall collision
        {
        b.setX(windowWidth - PADDING - BUBBLE_SIZE / 2);
        b.ricochet();
    }
    
    if (b.getY() - (float)BUBBLE_SIZE * COLLISION_OFFSET_MULTIPLIER / 2 < PADDING) // ceiling collision
        {
        println("ceiling collision detected!");
        b.stop();
        b.setY(PADDING + BUBBLE_SIZE / 2);
        bubbleGrid.snapCeiling(b);
    }
    
    for (Bubble bubble : bubbles) //bubble collision
        {
        if (b.dist(bubble) < (float)BUBBLE_SIZE * COLLISION_OFFSET_MULTIPLIER && b != bubble)
            {
            println("collision detected!");
            b.stop();
            bubbleGrid.snap(b, bubble);
        }
    }
}

void update()
{
    float oldTime = this.timeElapsed;
    this.timeElapsed = (float)millis() / 1000;
    float deltaT = this.timeElapsed - oldTime;
    
    if (isReloadingCannon)
    {
        reloadCannon(deltaT);
    }
    
    for (Bubble b : bubbles)
    {
        b.update();
        handleCollisions(b);
    }
    
    cannon.update(deltaT);
    ceiling.update(deltaT);
}

void draw()
{
    update();
    
    background(PLAYSPACE_COLOR);
    if (DEBUG_MODE)
    {
        bubbleGrid.drawDebug();
    }
    cannon.draw();
    drawBubbles();
    ceiling.draw();
}

void drawBubbles()
{
    for (Bubble b : bubbles)
    {
        b.draw();
    }
}