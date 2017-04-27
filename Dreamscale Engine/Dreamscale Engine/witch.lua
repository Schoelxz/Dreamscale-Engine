witch = {
    name="Lucia",
    interact=function(witch, player)
        if(player.hp == player.maxHp) then
            witch:say("Hi! Come back when you're wounded.")
        else
            witch:say("Hi! Let me heal you.")
	    player.hp = player.maxHp
        end
    end
}