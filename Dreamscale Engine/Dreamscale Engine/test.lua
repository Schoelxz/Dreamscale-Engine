
-- :=Funktion .=Static
-- property = foo 
-- function = foo()

--property set = foo = x
--property get = x = foo

--asdf3 = GameEngine.SfmlObject("BlueRectangle");

--asdf = GameEngine.FindObject("BlueRectangle"); --Finds the first element with the name BlueRectangle and changes THAT instance (only) with specified values.
--asdf:SetPosition(250, 500);
--asdf:SetSize(300, 300);

dse = GameEngine.Engine();

--wow = GameEngine.SfmlObject("yo2");
--rect = GameEngine.FindObject("yo2");

--rect:SetPosition(100, 500);
--rect:SetSize(50,400);

tmxhandler = dse:GetTmxHandler();

--circleshape = GameEngine.CircleShape();

--circleshape.position = GameEngine.Vector2f(400, 300);
--circleshape.radius = 130;
tmxhandler:ParseAllMaps();
dse:StartUpdate();







