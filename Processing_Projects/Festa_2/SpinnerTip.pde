class SpinnerTip
{
    float x;
    float y;
    float width;
    color drawColor;
    color circleColor;
    color ringColor;
    // float rotationAngle;

    public SpinnerTip(float x, float y, float width, color drawColor, color circleColor, color ringColor)
    {
        this.x = x;
        this.y = y;
        this.width = width;
        this.drawColor = drawColor;
        this.circleColor = circleColor;
        this.ringColor = ringColor;
        // this.rotationAngle = rotationAngle;
    }

    public void draw()
    {
        pushMatrix();
        rectMode(CENTER);
        translate(this.x,this.y);
        // rotate(this.rotationAngle);
        fill(this.drawColor);
        rect(0, -50, width, width * 2.5, width / 2);
        circle(0, -125, width * 1.5);
        fill(this.ringColor);
        circle(0, -125, width * 1.1);
        fill(this.circleColor);
        circle(0, -125, width * 0.7);
        
        noStroke();
        popMatrix();
    }
}