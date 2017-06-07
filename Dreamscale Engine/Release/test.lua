
object = GameEngine.SfmlObject("BlueRectangle");
object:SetPosition(50,50);
object:SetSize(300, 300);

asdf = GameEngine.FindObject("BlueRectangle"); --Finds the first element with the name BlueRectangle and changes THAT instance (only) with specified values.
asdf:SetPosition(250, 500);
asdf:SetSize(50, 70);
