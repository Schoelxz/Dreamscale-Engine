
-- :=Funktion .=Static
-- property = foo 
-- function = foo()

--property set = foo = x
--property get = x = foo

--asdf3 = GameEngine.SfmlObject("BlueRectangle");

--asdf = GameEngine.FindObject("BlueRectangle"); --Finds the first element with the name BlueRectangle and changes THAT instance (only) with specified values.
--asdf:SetPosition(250, 500);
--asdf:SetSize(300, 300);

gameEngine = GameEngine.Engine();
tmxhandler = gameEngine:GetTmxHandler();

--circleshape = GameEngine.CircleShape();

--circleshape.position = GameEngine.Vector2f(400, 300);
--circleshape.radius = 130;
tmxhandler:ParseAllMaps();
gameEngine:StartUpdate();







