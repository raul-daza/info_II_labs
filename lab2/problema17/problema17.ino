// C++ code
//
void setup()
{
  Serial.begin(115200);
  Serial.println();
}

void loop()
{
  int num, sum1 = 0, sum2 = 0, sum3 = 0;
  Serial.print("ingrese un numero: ");
  while(Serial.available() == 0){}
  num = Serial.readStringUntil('\n').toInt();
  Serial.println();
  for (int i = 1; i <= num/2; i++)
  {
    if (num%i == 0)
    {
      sum1 += i;
    }
  }
  for (int i = 1; i <= num; i++)
  {
    for (int j = 1; j <= i/2; j++)
    {
      if (i%j == 0)
      {
        sum2 += j;
      }
    }
    if (sum1 == i && sum2 == num)
    {
      sum3 += i;
    }
    sum2 = 0;
  }
  Serial.print("el resultado de la suma es: ");
  Serial.println(sum3 + num);
}