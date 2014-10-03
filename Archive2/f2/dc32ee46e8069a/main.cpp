
        //------------------------- 0.035% chance of spawning unicorns in Iron Will -----------------
        var zebras = this.game.resPool.get("zebras");

        if (this.game.ironWill) {
            var archery = this.game.science.get("archery");
            var unicorns = this.game.resPool.get("unicorns");
            if (this.game.rand(100000) <= 17 && unicorns.value < 2 && archery.researched) {
                unicorns.value += 1;
                this.game.msg("A unicorn comes to your village attracted by the catnip scent!");
            }

            if (!zebras.value && archery.researched) {
                zebras.value += 1;
                this.game.msg("A mysterious hunter from zebra tribe decides to stop over in the village.");
            } else if (zebras.value > 0 && zebras.value < this.game.karmaZebras) {    //zebra revolution
                if (this.game.rand(100000) <= 500) {
                    zebras.value += 1;
                    this.game.msg("Another zebra hunter joins your village.");
                    this.game.render();
                }
            }