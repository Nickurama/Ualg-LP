class Cannon
{
    final private float MAX_ANGLE = PI / 3; // 60º
    final private float ROTATION_ANGLE = PI / 18; // 10º
    final private float ROTATION_SPEED = PI / 4; // 45º/s
    final private int HEIGHT_WIDTH_RATIO = 3; // 3:1 height:width
    
    private int x;
    private int y;
    private int size;
    private color drawColor;
    private float angle;
    
    private boolean isRotating;
    private int rotationSign;
    private int rotationsIndex;

    private Bubble loadedBubble;
    
    public Cannon(int x, int y, int size, color drawColor)
    {
        this.x = x;
        this.y = y;
        this.size = size;
        this.drawColor = drawColor;
        
        this.angle = 0;
        this.isRotating = false;
        this.rotationsIndex = 0;
    }
    
    public void rotateLeft()
    {
        if (angle > - MAX_ANGLE && !isRotating)
        {
            isRotating = true;
            rotationSign = -1;
            rotationsIndex += -1;
        }
    }
    
    public void rotateRight()
    {
        if (angle < MAX_ANGLE && !isRotating)
        {
            isRotating = true;
            rotationSign = 1;
            rotationsIndex += 1;
        }
    }
    
    private void applyRotation(float deltaT) //in seconds
    {
        float ammountToRotate = rotationSign * ROTATION_SPEED * deltaT;
        angle += ammountToRotate;
        
        if ((rotationSign == 1 && angle >= rotationsIndex * ROTATION_ANGLE) || 
           (rotationSign == -1 && angle <= rotationsIndex * ROTATION_ANGLE))
        {
            angle = rotationsIndex * ROTATION_ANGLE; // snaps into correct angle
            isRotating = false;
        }
    }

    public void loadBubble(Bubble bubble)
    {
        loadedBubble = bubble;
        loadedBubble.setPos(this.x, this.y);
    }

    public void shoot()
    {
        loadedBubble.launch(angle - PI / 2); //cannon's 0º is up
    }
    
    public void update(float deltaT)
    {
        loadedBubble.update();
        if (isRotating)
        {
            applyRotation(deltaT);
        }
    }
    
    public void draw()
    {
        loadedBubble.draw();
        pushMatrix();
        translate(x,y);
        rectMode(CENTER);
        stroke(BLACK);
        strokeWeight(size / 10);
        rotate(angle);
        fill(drawColor);
        rect(0, 0, size, HEIGHT_WIDTH_RATIO * size, 0, 0, size / 2, size / 2);
        popMatrix();
    }
}