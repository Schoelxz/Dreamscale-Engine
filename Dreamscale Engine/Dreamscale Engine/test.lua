
-- :=Funktion .=Static
-- property = foo 
-- function = foo()

--property set = foo = x
--property get = x = foo

asdf3 = GameEngine.SfmlObject("BlueRectangle");

asdf = GameEngine.FindObject("BlueRectangle"); --Finds the first element with the name BlueRectangle and changes THAT instance (only) with specified values.
asdf:SetPosition(250, 500);
asdf:SetSize(300, 300);


asdf2 = GameEngine.Engine();
--asdf2:GetTmxHandler();
tmxhandler = asdf2:GetTmxHandler();
--tmxhandler:ParseAllMaps();
asdf2:StartUpdate();
--tmxhandler:ParseAllMaps();
--asdf2:StartUpdate();

--asdf2 = GameEngine.Engine();
--asdf2:StartUpdate();





















































--deadMansLand

-- script rectangles

--blueRect = GameEngine.FindObject("BlueRectangle");

--blueRect:SetPosition(200, 200);
--blueRect:SetSize(300, 300);


--

--asdf2 = GameEngine.SfmlObject();
--asdf2:SetPosition(100, 100);
--asdf2:SetSize(75, 500);

--asdf3 = GameEngine.SfmlObject.FindObject("BlueRectangle");


--asdf3:SetSize(500,500);

-- script.lua


--function add(x, y)
	--return x + y
--end

--a = GameEngine.A();
--b = GameEngine.B();

--a:Print();
--b:Print();