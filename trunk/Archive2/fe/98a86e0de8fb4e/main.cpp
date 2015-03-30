Say I have a spell object of the form:

Spell {
    name
	element_type
	caster
	target_list
	damage
}

and such. Let's create a Spell called Fireball:

Fireball (is a Spell) {
	name = Fireball
	element_type = fire
	caster = <a pointer or reference to the caster>
	target_list = <a single node with a reference to the target unit>
	damage = 15
}

Now, say we want to design a Poison spell. Oops, our current data structure
doesn't even allow for calling a specific data structure! So we need to REFACTOR.

Poison {
	name = Poison
	element_type = poison
	caster = <reference>
	target_list <reference>
	function = <some function of the form f(&caster, &target_list)>
}

Good. Now we can use a functor or some other thing to wrap the functionality
of a Poison spell. Now we can do things like have the function wrap different
calls to reduce health, change status effects, etc.

Now, say we want a player to be able to have different levels of Poison.
I will use a new spell called Curse.

Curse will:
	* Do damage on-hit.
	* Add 1 stack of Curse to the targets(s)
	* Do extra damage based on the amount of stacks of Curse on the target(s)

Oops, now we need to REFACTOR our code to support a stacking buff system!
We'll need to design a new status_effect or Effect class or data structure:


Status {
	name
	type
	appliedBy/applier/camefrom/fromEntity/etc. (see, naming problems!)
	stacks (an integer)
}

Okay good, now all we have to do is have each Entity or Unit hold a list of Status
objects and have Spells iterate through the list to find a status.

We do not have to change our data structure.

Now, let's say that we want to change the effects of the Spell based on our
environment. Say, a Spell is now weaker if it's within a "Holy" environment.
Okay then, let's just design an Environment data structure for our functions
to access:

Environment {
	name
	type
	attribute_list
}

Okay, good. Now we can host one single Environment object for every map or so
that we walk into. Say we have a new Cathedral environment to counter Curse:

Cathedral (is of type Environment) {
	name = Cathedral
	type = indoor (is this really such a good thing?)
	attribute_list = holy, roofed, indoors, warm
}

Now we can have Curse just ask for an Environment object to look at when it needs
to extract a certain environment attribute. Good!

Now, what if we want spells to change or affect or create a zone that changes
the environment locally or globally for an entire map or world?

Well, now we need spells to change the Environment. We need to create en entire
API to encapsulate the Environment and decide who control the Environment.

This means we'll probably want to limit the amount of changes per second, have a 
priority system for who can override which changes, and etc.

So, how about we just use our Status system and apply it to the Environment?

We REFACTOR once again. Now our Environment class looks like this:

Environment {
	name
	Status_list
}

There. Now if we want to change additional attributes like Rainy, Sunny, or
Acidic to affect Spells and combat, we can!

Now, how do we solve the issue of local environment changes? Well, this is a
problem. Now, we either need to change our functions such that we can check for
local auras or changes based on proximity (which is dangerous in terms of taking
up networking and computing power for large multiplayer games and servers).

I have an idea: how about we have our Environment APPLY a Status to players as
they come into a room or environment, reading from an immutable variable? Then,
we can change code in only one place--the Environment. If we ever want to change
the Environment, we can then just create dummy Entity or Unit objects to nullify
the Environment statuses and apply new ones based on Proximity. Additionally, this
allows us to spawn local Environment effects to dynamically affect spells on the fly!

But, this means we REFACTOR our code once again. The API has changed once again.
Now, let's say we want a system to require more than one player to put their
powers together to cast a spell. Remember our original (or multi-refactored) data
structure?

Spell {
	name
	element_type
	caster
	target_list 
	function
}

Well, we need to change caster to caster_list for this.

Spell {
	name
	element_type
	caster_list
	target_list
	function
}

Eek. Now, what if we need multiple element_types for a spell? Eek! REFACTOR!

Spell {
	name
	element_type_list
	caster_list
	target_list
	function
}

And by now, our data structure is getting increasingly difficult to maintain and
also compute, especially in a large multi-user setting with simultaneous, real time
changes.

And there are many, many other wacky ideas we want to try:

 * Change the effects of a spell based on what a player is named or wearing
 * Allow the player to absorb damage and release it in a separate stack system
 * Create a combo system
 * Create a berzerker system where rage unlocks new spell effects or functions
 * Allow spells to evolve into new types based on use or Environment
 * Allow spells to change based on past use (function objects, anyone, and storing state?)
 * Allow spells to be composed of other spells and combine to create a new one
	based on the attributes of the former
	* This also means we'll need to REFACTOR once again to define types of spells
		as well as their attributes.
 * Allow spells to have different effects based on what spells were cast recently.

///////
///////
///////
THE CONCLUSION:
///////
///////
///////

Find how many times we had to say refactor. It's all in CAPS already.
That's more than once, and more than twice. Game like MapleStory, I bet, tried to
make their system more flexible to attract more players, but couldn't. Based on legacy code,
it could only support so much more. Notice how MapleStory 2 appears to be more flexible.
However, I bet it'll hit a wall too.

The point is to create a game such that its system remains open to new design decisions.
Though the programming may be quite messy and not optimal, it is highly-desirable to have
freedom in design to allow designers to do "the new thing" within your own system.

And finally... HOW DO YOU TRANSMIT ALL THIS INFORMATION?
With a rigid, static data type, code must change often. If you try to implement a more
dynamic data messaging system, switching from one format to another is quite trivial and
just requires putting in more listeners within the scripts for new data fields.

Allowing the insertion of new data fields or types is great for design--you're not changing
the system itself, just the design on top of the system. And this is what we want--we want to
change scripts, not the underlying framework.


