class BubbleCell
{
    final private int DEBUG_CIRCLE_SIZE = 50;
    
    private float x;
    private float y;
    private int row;
    private int column;
    private Bubble bubble;
    private boolean hasBubble;
    private boolean isConnected;
    
    public BubbleCell(float x, float y, int row, int column)
    {
        this.x = x;
        this.y = y;
        this.row = row;
        this.column = column;
        hasBubble = false;
    }
    
    public void setBubble(Bubble b)
    {
        if (hasBubble)
        {
            println("Error: bubble overlap!: (" + this.row + "," + this.column + ").");
        }
        this.bubble = b;
        b.setX(this.x);
        b.setY(this.y);
        hasBubble = true;
    }
    
    public void removeBubble()
    {
        if (hasBubble)
        {
            hasBubble = false;
        }
    }
    
    public void debugDraw()
    {
        noFill();
        strokeWeight(DEBUG_CIRCLE_SIZE / 20);
        stroke(BLACK);
        circle(x, y, DEBUG_CIRCLE_SIZE);
    }
    
    public boolean hasBubble() { return hasBubble; }
    public Bubble getBubble() { if (hasBubble) { return this.bubble; } else { return null; } }
    public float getX() { return this.x; }
    public void setX(float x)
    {
        this.x = x;
        if (this.hasBubble())
            this.bubble.setX(x);
    }
    public float getY() { return this.y; }
    public void setY(float y)
    {
        this.y = y;
        if (this.hasBubble())
            this.bubble.setY(y);
    }
    public int getRow() { return this.row; }
    public int getColumn() { return this.column; }
    public boolean isConnected() { return this.isConnected; }
    public void setConnected() { this.isConnected = true; }
    public void setDisconnected() { this.isConnected = false; }
}