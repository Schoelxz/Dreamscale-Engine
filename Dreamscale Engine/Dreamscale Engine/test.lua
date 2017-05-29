
-- :=Funktion .=Static
-- property = foo 
-- function = foo()

--property set = foo = x
--property get = x = foo

asdf3 = GameEngine.SfmlObject("BlueRectangle");

asdf = GameEngine.FindObject("BlueRectangle"); --Finds the first element with the name BlueRectangle and changes THAT instance (only) with specified values.
asdf:SetPosition(250, 500);
asdf:SetSize(300, 300);


engine = GameEngine.Engine();

tmxhandler = engine:GetTmxHandler();
tmxhandler:ParseAllMaps();
engine:StartUpdate();

