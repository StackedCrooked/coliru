// --- proof of concept ---
struct brick {
    explicit brick(int) {}
    brick(brick const&) = delete;
    brick(brick&&) = delete;
    brick& operator=(brick const&) = delete;
    brick& operator=(brick&&) = delete;
};

brick make_brick(int n) {
    return { n }; // no fucking way to get this right at all ever this is why I am always reluctant for new syntax because it gets full of fucking corner cases and FUCK IF WE DON'T HAVE ENOUGH CORNER CASES ALREADY AAAAAAAAAAAAAAHHHHHHHHHHH NIPPLE SALADS! Nipple salads... NIPPLE SALADS! NEVER STOP THE KILLING!! NEVER!! I'LL SLICE YOUR EYELIDS SO YOU CAN WATCH THE END!! I know what I have become... I am the inside of this world... I taste the gore, and I smell the crying... AND I WANT MORE! I want to bathe in your flesh, I want to savor your fear. I wanna live inside a castle built of your agony, AND I WANT TO CRUMBLE IT WITH AN AXE TO YOUR CAROTID ARTERY! NOW YOU SHOULD BE SCARED! Now to SCRAPE YOUR FACE FROM MY FINGERNAILS! NIPPLE SALADS! Nipple salads... NIPPLE SALADS! 
}
