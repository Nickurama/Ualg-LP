class Spinner
{
    final float rotationOffset = 2 * PI / 3;

    SpinnerTip tip1;
    SpinnerTip tip2;
    SpinnerTip tip3;
    float x;
    float y;
    float rotationAngle;
    float tipWidth;
    color drawColor;

    float rotationSpeed;
    final float dragCoefficient = 2 * PI;

    int spins;
    float rotatedAmmount;
    int RPS;
    int maxRPS;

    public Spinner(float x, float y, float rotationAngle, float tipWidth, color drawColor, color ringColor, color color1, color color2, color color3)
    {
        this.x = x;
        this.y = y;
        this.rotationAngle = rotationAngle;
        this.tipWidth = tipWidth;
        this.drawColor = drawColor;
        tip1 = new SpinnerTip(0, 0, tipWidth, drawColor, color1, ringColor);
        tip2 = new SpinnerTip(0, 0, tipWidth, drawColor, color2, ringColor);
        tip3 = new SpinnerTip(0, 0, tipWidth, drawColor, color3, ringColor);
        rotationSpeed = 0;
        spins = 0;
        rotatedAmmount = 0;
        RPS = 0;
        maxRPS = 0;
    }

    public void update(float deltaT)
    {
        float previousRotationAngle = rotationAngle;
        float previousRotationSpeed = rotationSpeed;
        if (rotationSpeed > 0)
        {
            rotationSpeed += deltaT * -dragCoefficient;
        }
        else if (rotationSpeed < 0)
        {
            rotationSpeed += deltaT * dragCoefficient;
        }
        if (previousRotationSpeed * rotationSpeed < 0)
        {
            rotationSpeed = 0;
        }
        rotationAngle += deltaT * rotationSpeed;
        rotatedAmmount += abs(rotationAngle - previousRotationAngle);
        if(rotatedAmmount >= 2 * PI)
        {
            spins++;
            rotatedAmmount -= 2 * PI;
        }
    }

    public void draw()
    {
        pushMatrix();
        noStroke();
        translate(x,y);
        rectMode(CENTER);
        rotate(rotationAngle);
        tip1.draw();
        rotate(rotationOffset);
        tip2.draw();
        rotate(rotationOffset);
        tip3.draw();
        stroke(BLACK);
        strokeWeight(3);
        fill(drawColor);
        circle(0, 0, tipWidth * 0.8);
        popMatrix();
    }
}