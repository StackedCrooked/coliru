#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <chrono>
#include <sstream>

using my_string = std::shared_ptr<const std::string>;
template<typename... T>
my_string make_string( T&&... t ) {
  return std::unique_ptr<std::string>( new std::string(std::forward<T>(t)...) );
}
struct order_ptrs_by_value {
  template<class T, class U>
  bool operator()( T&& t, U&& u ) const {
    	if (!t || !u) return t < u;
    return (*t) < (*u);
  }
};
struct equal_ptrs_by_value {
  template<class T, class U>
  bool operator()( T&& t, U&& u ) const {
		if (!t || !u) return t == u;
    return (*t) == (*u);
  }
	
};
struct hash_string {
	template<typename T>
	std::size_t element_hash(T const& t) const { return std::hash<T>{}(t); }
	std::size_t operator()(my_string const& s) const {
		std::size_t seed = 0;
		if (!s) return seed;
		for (auto&& c : *s) {
			seed ^= element_hash(c) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

char const buff[]=R"(*************************************************************************
**                         Thesaurus-1911                              **
**             Version 1.02  (supplemented: July 18, 1991)             **
*************************************************************************
An electronic thesaurus derived from the version of Roget's Thesaurus
published in 1911.

     This core thesaurus is provided along with the unabridged Moby Thesaurus
main corpus to frame the traditional concept divisions that may be useful
if the licensee is considering converting the flat-file Moby Thesaurus to
the concept/index scheme.  Note that no index is herein provided -- it is
presumed that a subset of the 30,000 roots in Moby Thesaurus II will be used
to generate the user's custom index.

     Note that this version of Thesaurus-1911 has been supplemented with
over 1,000 words not present in the original 1911 edition, but many modern
words are still missing.  About 1500 verbs (out of 6500) which can be found
in an 80,000-word spell-checker are absent from this work.  The deficiency
of nouns is probably much worse, especially on technical topics.  Of 40,000
unique words contained in the original text, 12,000 are not recognized by a
spell-checker.  Most of these are foreign words(primarily Latin), and many
are obsolete.  In this version, these words are marked as such by comments
in square brackets.  Although this version has been proof-read, there are
doubtless numerous residual transcription errors, some of which may be
obvious even without reference to the original text.  We will be grateful
if any of these are brought to our attention; the corrections will appear
in subsequent versions.

     In this file, comments which are not a proper part of the thesaurus
itself are contained within arrow brackets thus: <-- comment -->.
     Section headings,  which are not an actual part of the thesaurus
proper, are included between percent (%) markers.
     Occasional references to numbers starting with "@" are the embryonic
beginnings of a reorganized version, mentioned below.  A few comments are
also included within curly brackets {}.
          ============================================

  The following additional differences will be noted between this version
and the original edition of the printed 1911 thesaurus:
  (1)  the space-saving abbreviations in the original, using hyphens to
represent common words, prefixes or suffixes, have been expanded into the
full words or phrases.
  (2) the side-by-side format for words and their opposites has been
abandoned.  Words are listed in order of their entry number.
  (3)  each main entry (1035 entries) has a pound sign "#" in front of the
number to facilitate computerized search.
  (4) greek words and phrases are transliterated and included between
brackets in the format <gr/greek word/gr>.
  (5)  where italics occurred in the original, italics are used in the
Microsoft Word format file.  In the plain ASCII file, this formatting is
lost.
  (6)  in the original book, words which were obsolete (in 1911) were
marked with a dagger.  In this version, those words are marked with a
vertical bar ("|").
     Some of the words which were still current in 1911, but are no longer
found in a current college-size dictionary (presently obsolete words), or
which are no longer used in the specific indicated sense, have been marked
with a bar followed by an exclamation point "|!".  However, this marking
process has just commenced, and only a small portion of the words which are
now obsolete have been thus marked.  Most though not all of the foreign-
language phrases are now obsolete.
     The "obsolete" notation [obs3] indicates that the previous word (or
some word in the previous phrase) is not recognized by the word processor's
spelling checker, and also is either NOT in a modern college-sized
dictionary, or is noted there as being "ARCHAIC".
  (7)  the approximate location of the bottom of each page in the original
1911 printed book is indicated by a comment of the form: <--  p.  23 -->.
To search for a page, note that there are two spaces between the "p." and
the page number.
  (8)  This file contains only the main body of the thesaurus.  Neither
outline nor index are contained here.

==========================================================================
               THESAURUS OF ENGLISH WORDS AND PHRASES

                              CLASS I
               WORDS EXPRESSING ABSTRACT RELATIONS

                    SECTION I. EXISTENCE

1. BEING, IN THE ABSTRACT
%

     #1.  Existence.-- N. existence, being, entity, ens[Lat], esse[Lat],
subsistence.
     reality, actuality; positiveness &c. adj.; fact, matter of fact, sober
reality; truth &c. 494; actual existence.
     presence &c. (existence in space) 186; coexistence &c. 120.
     stubborn fact, hard fact; not a dream &c. 515; no joke.
     center of life, essence, inmost nature, inner reality, vital
principle.
     [Science of existence], ontology.
     V. exist, be; have being &c. n.; subsist, live, breathe, stand,
obtain, be the case; occur &c. (event) 151; have place, prevail; find
oneself, pass the time, vegetate.
     consist in, lie in; be comprised in, be contained in, be constituted
by.
     come into existence &c. n.; arise &c. (begin) 66; come forth &c.
(appear) 446.
     become &c. (be converted) 144; bring into existence &c. 161.
     abide, continue, endure, last, remain, stay.
     Adj. existing &c. v.; existent, under the sun; in existence &c. n.;
extant; afloat, afoot, on foot, current, prevalent; undestroyed.
     real, actual, positive, absolute; true &c. 494; substantial,
substantive; self-existing, self-existent; essential.
     well-founded,  well-grounded; unideal[obs3], unimagined; not potential
&c. 2; authentic.
     Adv. actually &c. adj.; in fact, in point of fact, in reality; indeed;
de facto, ipso facto.
     Phr. ens rationis[Lat]; ergo sum cogito: "thinkest thou existence doth
depend on time?" [Lat][Byron].


     #2. Inexistence.-- N. inexistence[obs3]; nonexistence, nonsubsistence;
nonentity, nil; negativeness &c. adj.; nullity; nihility[obs3], nihilism;
tabula rasa[Lat], blank; abeyance; absence &c. 187; no such thing &c. 4;
nonbeing, nothingness, oblivion.
     annihilation; extinction &c. (destruction) 162; extinguishment,
extirpation, Nirvana, obliteration.
     V. not exist &c. 1; have no existence &c. 1; be null and void; cease
to exist &c. 1; pass away, perish; be extinct, become extinct &c. adj.; die
out; disappear &c. 449; melt away, dissolve, leave not a rack behind; go,
be no more; die &c. 360.
     annihilate, render null, nullify; abrogate &c. 756; destroy &c. 162;
take away; remove &c. (displace) 185; obliterate, extirpate.
     Adj. inexistent[obs3], nonexistent &c. 1; negative, blank; missing,
omitted; absent &c. 187,; insubstantial, shadowy, spectral, visionary.
     unreal, potential, virtual; baseless, in nubibus[Lat]; unsubstantial
&c. 4; vain.
     unborn, uncreated[obs3], unbegotten, unconceived, unproduced, unmade.
     perished, annihilated, &c. v.; extinct, exhausted, gone, lost,
vanished, departed, gone with the wind; defunct &c. (dead) 360.
     fabulous, ideal &c. (imaginary) 515, supposititious &c. 514.
     Adv.  negatively, virtually &c. adj.
     Phr. non ens[Lat].

<--  p.  1  -->

%
2. BEING, IN THE CONCRETE
%

     #3. Substantiality. -- N. substantiality, hypostasis; person, being,
thing, object, article, item; something, a being, an existence; creature,
body, substance, flesh and blood, stuff , substratum; matter &c. 316;
corporeity[obs3], element, essential nature, groundwork, materiality,
substantialness, vital part.
     [Totality of existences], world &c. 318; plenum.
     Adj. substantive, substantial; hypostatic; personal, bodily, tangible
&c. (material) 316; corporeal.
     Adv. substantially &c. adj.; bodily, essentially.



     #4. Unsubstantiality. -- N. unsubstantiality[obs3], insubstantiality;
nothingness, nihility[obs3]; no degree, no part, no quantity, no thing.
     nothing, naught, nil, nullity, zero, cipher, no one, nobody; never a
one, ne'er a one[contr]; no such thing, none in the world; nothing
whatever, nothing at all, nothing on earth; not a particle &c. (smallness)
32; all talk, moonshine,  stuff and nonsense; matter of no importance,
matter of no consequence. thing of naught, man of straw, John Doe and
Richard Roe, faggot voter; nominis umbra[Lat], nonentity; flash in the pan,
vox et praeterea nihil[Lat].
     shadow; phantom &c.(fallacy of vision) 443; dream &c. (imagination)
515; ignis fatuus &c. (luminary) 423[Lat]; " such stuff as dreams are made
of " [Tempest]; air, thin air, vapor; bubble &c. 353; " baseless fabric of
a vision " [Tempest]; mockery.
     hollowness, blank; void &c. (absence) 187.
     inanity, fool's paradise.
     V. vanish, evaporate, fade, dissolve, melt away; disappear &c. 449.
     Adj. unsubstantial; baseless, groundless; ungrounded; without
foundation, having no foundation.
     visionary &c. (imaginary) 515; immaterial &c. 137; spectral &c. 980;
dreamy; shadowy; ethereal, airy; cloud built, cloud formed; gossamery,
illusory, insubstantial, unreal.
     vacant, vacuous; empty &c. 187; eviscerated; blank, hollow; nominal;
null; inane.
     Phr. there's nothing in it; " an ocean of dreams without a sound"
[Shelley].

%
3. FORMAL EXISTENCE

Internal conditions
%

     #5. Intrinsicality.-- N. intrinsicality[obs3], inbeing[obs3],
inherence, inhesion[obs3]; subjectiveness; ego; egohood[obs3]; essence,
noumenon; essentialness[obs3] &c. adj.; essential part, quintessence,
incarnation, quiddity, gist, pith, marrow, core, sap, lifeblood, backbone,
heart, soul; important part &c. (importance) 642.
     principle, nature, constitution, character, type, quality,
crasis[obs3], diathesis[obs3].
     habit; temper, temperament; spirit, humor, grain; disposition.
     endowment, capacity; capability &c. (power) 157.
     moods, declensions, features, aspects; peculiarities &c. (speciality)
79; idiosyncrasy, oddity; idiocrasy &c. (tendency) 176[obs3]; diagnostics.
     V. be in the blood, run in the blood; be born so; be intrinsic &c.
adj.
     Adj. derived from within, subjective; intrinsic, intrinsical[obs3];
fundamental, normal; implanted, inherent, essential, natural; innate,
inborn, inbred, ingrained, inwrought; coeval with birth, genetous[obs3],
haematobious[obs3], syngenic[obs3]; radical, incarnate, thoroughbred,
hereditary, inherited, immanent; congenital, congenite|; connate, running
in the blood; ingenerate[obs3], ingenite|; indigenous; in the grain &c. n.;
bred in the bone, instinctive; inward, internal &c. 221; to the manner
born; virtual.
     characteristic &c. (special) 79, (indicative) 550; invariable,
incurable, incorrigible, ineradicable, fixed.
     Adv. intrinsically &c. adj.; at bottom, in the main, in effect,
practically, virtually, substantially, au fond; fairly.
     Phr. " character is higher than intellect " [Emerson]; "come give us a
taste of your quality "  magnos homines virtute metimur non fortuna [Lat][
Hamlet][Nepos]; non numero haec judicantur sed pondere [Lat][Cicero]; "
vital spark of heavenly flame " [Pope].


%
External conditions
%

     #6. Extrinsicality.-- N. extrinsicality[obs3], objectiveness, non ego;
extraneousness &c. 57; accident; appearance, phenomenon &c. 448.
     Adj. derived from without; objective; extrinsic, extrinsical[obs3];
extraneous &c. (foreign) 57; modal, adventitious; ascititious[obs3],
adscititious[obs3]; incidental, accidental, nonessential; contingent,
fortuitous.
     implanted, ingrafted[obs3]; inculcated, infused.
     outward, apparent &c. (external) 220.
     Adv. extrinsically &c. adj.


<--  p.  2  -->

4. MODAL EXISTENCE

Absolute
     #7. State. -- N. state, condition, category, estate, lot, ease, trim,
mood, pickle, plight, temper; aspect &c. (appearance) 448, dilemma, pass,
predicament.
     constitution, habitude, diathesis[obs3]; frame, fabric &c. 329; stamp,
set, fit, mold, mould.
     mode, modality, schesis[obs3]; form &c. (shape) 240.
     tone, tenor, turn; trim, guise, fashion, light, complexion, style,
character.
     V. be in a state, possess a state, enjoy a state, labor under a state
&c. n.; be on a footing, do, fare; come to pass.
     Adj. conditional, modal, formal; structural, organic.
     Adv. conditionally &c. adj.; as the matter stands, as things are; such
being the case &c. 8.
%
                    Relative
%
     
     #8. Circumstance. -- N. circumstance, situation, phase, position,
posture, attitude, place, point; terms; regime; footing, standing, status.
     occasion, juncture, conjunctive; contingency &c. (event) 151.
     predicament; emergence, emergency; exigency, crisis, pinch, pass,
push; occurrence; turning point.
     bearings, how the land lies.
     surroundings, context, environment 229a[TE 232]; location 184.
     contingency, dependence (uncertainty) 475; causation 153, attribution
155.
     Adj. circumstantial; given, conditional, provisional; critical; modal;
contingent, incidental; adventitious &c. (extrinsic) 6; limitative[obs3].
     Adv. in the circumstances, under the circumstances &c. n., the
circumstances, conditions &c. 7; thus, in such wise.
     accordingly; that being the case, such being the case, in view of the
circumstances; that being so, sith[obs3], since, seeing that.
     as matters stand; as things go, as times go.
     conditionally, provided, if, in case; if so,   if so be, if it be so;
depending on circumstances, in certain circumstances, under certain
conditions; if it so happen, if it so turn out; in the event of; in such a
contingency,  in such a case, in such an event; provisionally, unless,
without.
     according to circumstances, according to the occasion; as it may
happen, as it may turn out,as it may  be; as the case may be, as the  wind
blows; pro re nata[Lat].
     Phr. " yet are my sins not those of circumstance " [Lytton].

<--  p.  3  -->


SECTION II. RELATION

. 1. ABSOLUTE RELATION
     #9. Relation. -- N. relation, bearing,  reference, connection,
concern,. cognation ; correlation &c. 12; analogy; similarity &c. 17;
affinity, homology, alliance, homogeneity, association; approximation &c.
(nearness) 197; filiation &c. (consanguinity) 11[obs3]; interest; relevancy
&c. 23; dependency, relationship, relative position.
     comparison &c. 464; ratio, proportion.
link, tie, bond of union.
     V. be related &c. adj.; have a relation &c. n.; relate to, refer to;
bear upon, regard, concern, touch, affect, have to do with; pertain to,
belong to, appertain to; answer to; interest.
     bring into relation with, bring to bear upon; connect, associate, draw
a parallel; link &c. 43.
     Adj. relative; correlative &c. 12; cognate; relating to &c. v.;
relative to, in relation with, referable or referrible to[obs3]; belonging
to &c. v.; appurtenant to, in common with.
     related, connected; implicated, associated, affiliated, allied to; en
rapport, in touch with.
     approximative[obs3], approximating; proportional, proportionate,
proportionable; allusive, comparable.
     in the same category &c. 75; like &c. 17; relevant &c. (apt) 23;
applicable, equiparant[obs3].
     Adv. relatively &c. adj.; pertinently &c. 23.
     thereof; as to, as for, as respects, as regards; about; concerning &c.
v.; anent; relating to, as relates to; with relation, with reference to,
with respect to,with regard to; in respect of; while speaking of, a propos
of[Fr]; in connection with; by the way, by the  by; whereas; for as much
as, in as much as; in point of, as far as; on the part of,  on the score
of; quoad hoc[Lat]; pro re nata[Lat]; under the head of &c. (class) 75  of;
in the matter of, in re.
     Phr. " thereby hangs a tale " [Taming of the Shrew].

     #10. [Want, or absence of relation.]  Irrelation. -- N.
irrelation[obs3], dissociation; misrelation[obs3]; inapplicability;
inconnection[obs3]; multifariousness; disconnection &c. (disjunction) 44;
inconsequence, independence; incommensurability; irreconcilableness &c.
(disagreement) 24; heterogeneity; unconformity &c. 83; irrelevancy,
impertinence, nihil ad rem[Lat]; intrusion &c. 24; non-pertinence.
     V. have no relation to &c. 9; have no bearing upon, have no concern
with &c. 9 , have no business with; not concern &c. 9; have no business
there, have nothing to do with,
intrude &c. 24.
     bring in head and shoulders, drag in head and shoulders, lug in head
and shoulders.
     Adj. irrelative[obs3], irrespective, unrelated; arbitrary;
independent, unallied; unconnected, disconnected; adrift, isolated,
insular; extraneous, strange, alien, foreign, outlandish, exotic.
     not comparable, incommensurable, heterogeneous; unconformable &c. 83.
irrelevant, inapplicable; not pertinent, not to the, purpose; impertinent,
inapposite, beside the mark, a propos de bottes[Fr]; aside from the
purpose,, away from the purpose,, foreign to the purpose, beside the
purpose,  beside the question, beside the transaction,  beside the point;
misplaced &c. (intrusive) 24; traveling out of the record.
     remote, far-fetched, out of the way, forced, neither here nor there,
quite another thing; detached, segregate; disquiparant[obs3].
     multifarious; discordant &c. 24.
     incidental, parenthetical, obiter dicta, episodic.
     Adv. parenthetically &c. adj.; by the way, by the by; en passant[Fr],
incidentally; irrespectively &c. adj.; without reference to, without regard
to; in the abstract &c. 87; a se.
     
     #11. [Relations of kindred.] Consanguinity. -- N. consanguinity,
relationship, kindred, blood; parentage &c. (paternity) 166;
filiation[obs3], affiliation; lineage, agnation[obs3], connection,
alliance; family connection, family tie; ties of blood; nepotism.
     kinsman, kinfolk; kith and kin; relation, relative; connection;
sibling, sib; next of kin; uncle, aunt, nephew, niece; cousin, cousin-
german[obs3]; first cousin, second cousin; cousin once removed,  cousin
twice &c. removed; near relation, distant relation; brother,  sister, one's
own flesh and blood.
     family, fraternity; brotherhood, sisterhood, cousinhood[obs3].
race, stock, generation; sept &c. 166; stirps, side; strain; breed, clan,
tribe, nation.
     V. be related to &c. adj.  claim relationship with &c. n. with.
     Adj. related, akin, consanguineous, of the blood, family, allied,
collateral; cognate, agnate, connate; kindred; affiliated; fraternal.

<--  p.  4  -->

     intimately related, nearly related, closely related, remotely related,
distantly related,  allied; german.

     #12. [Double or reciprocal relation.] Correlation. -- N.
reciprocalness &c. adj[obs3].; reciprocity, reciprocation; mutuality,
correlation, interdependence, interrelation, connection, link, association;
interchange &c. 148; exchange, barter.
     reciprocator, reprocitist.
     V. reciprocate, alternate; interchange &c. 148; exchange;
counterchange[obs3].
     Adj. reciprocal, mutual, commutual[obs3], correlative, reciprocative,
interrelated, closely related; alternate; interchangeable; interdependent;
international; complemental, complementary.
     Adv. mutually, mutatis mutandis[Lat]; vice versa; each other, one
another; by turns &c. 148; reciprocally &c. adj.
     Phr. " happy in our mutual help " [Milton].

     #13. Identity. -- N. identity, sameness; coincidence, coalescence;
convertibility; equality &c. 27; selfness[obs3], self, oneself;
identification.
     monotony, tautology &c. (repetition) 104.
     facsimile &c. (copy) 21; homoousia: alter ego &c. (similar) 17[obs3];
ipsissima verba &c. (exactness) 494[Lat]; same; self, very , one and the
same; very thing, actual thing; real McCoy; no other; one and only; in the
flesh.
     V. be identical &c. adj.; coincide, coalesce, merge.
     treat as the same, render the same,  identical; identify; recognize
the identity of, .
     Adj. identical; self, ilk; the same &c. n. selfsame, one and the same,
homoousian[obs3].
     coincide, coalescent, coalescing; indistinguishable; one; equivalent
&c. (equal) 27; tweedle dee and tweedle dum[Lat]; much the same,  of a
muchness[obs3]; unaltered. .
Adv. identically &c. adj.; on all fours.


     #14. [Noncoincidence.] Contrariety. N. contrariety, contrast, foil,
antithesis, oppositeness; contradiction; antagonism &c. (opposition) 708;
clashing, repugnance.
     inversion &c. 218; the opposite, the reverse, the inverse, the
converse, the antipodes, the antithesis, the other extreme.
V. be contrary &c. adj.; contrast with, oppose; diller toto coelo[Lat].
     invert, reverse, turn the tables; turn topsy-turvy, turn end for end,
turn upside down, turn inside out.
     contradict, contravene; antagonize &c. 708.
     Adj. contrary, contrarious[obs3], contrariant[obs3]; opposite,
counter, dead against; converse, reverse; opposed, antithetical,
contrasted, antipodean, antagonistic, opposing; conflicting, inconsistent,
contradictory, at cross purposes; negative; hostile &c. 703. differing toto
coelo[Lat]; diametrically opposite; diametrically opposed; as opposite as
black and white, as opposite as light and darkness, as opposite as fire and
water, as opposite as the poles; as different as night and day; " Hyperion
to a satyr"[ Hamlet]; quite the contrary, quite the reverse ;no such thing,
just the other way, tout au contraire[Fr].
Adv. contrarily &c. adj.; contra, contrariwise, per contra, on the
contrary, nay rather; vice versa; on the other hand &c. (in compensation)
30.
     Phr. " all concord's born of contraries " [B. Jonson].  Thesis,
antithesis, synthesis [Marx].

     #15 Difference. -- N. difference; variance, variation, variety;
diversity, dissimilarity &c. 18; disagreement &c. 24; disparity &c.
(inequality) 28; distinction, contradistinction; alteration.
modification, permutation, moods and tenses.
     nice distinction, fine distinction, delicate distinction, subtle
distinction; shade of difference, nuance; discrimination &c. 465;
differentia.
     different thing, something else, apple off another tree, another pair
of shoes; horse of a different color; this that or the other.
     V. be different &c. adj.; differ, vary, ablude|, mismatch, contrast;
divaricate; differ toto coelo[Lat], differ longo intervallo[It].
     vary, modify &c. (change) 140.
     discriminate &c. 465.
     Adj. differing &c. v.; different, diverse, heterogeneous,
multifarious, polyglot; distinguishable, dissimilar; varied, modified;
diversified, various, divers, all manner of, all kinds of; variform &c.
81[obs3]; daedal[obs3].
     other, another, not the same; unequal &c. 28. unmatched; widely apart,
poles apart, distinctive, characteristic, ; discriminative; distinguishing.
     incommensurable, incommensurate.
Adv. differently &c. adj.
Phr. il y a fagots et fagots.

<--  p.  5  -->

%
2. CONTINUOUS RELATION
%

     #16. Uniformity. -- N. uniformity; homogeneity, homogeneousness;
consistency; connaturality[obs3], connaturalness[obs3]; homology;
accordance; conformity &c. 82; agreement &c. 23; consonance, uniformness.
regularity, constancy, even tenor,.routine; monotony.
     V. be uniform &c. adj.; accord with &c. 23; run through.
become uniform &c. adj.; conform to &c. 82.
     render uniform, homogenize &c. adj.; assimilate, level, smooth, dress.
     Adj. uniform; homogeneous, homologous;of a piece[Fr], consistent,
connatural[obs3]; monotonous, even, invariable; regular, unchanged,
undeviating, unvaried, unvarying.
     unsegmented.
     Adv. uniformly &c. adj.; uniformly with &c. (conformably) 82; in
harmony with &c. (agreeing) 23.
     always, invariably, without exception, without fail, unfailingly,
never otherwise; by clockwork.
Phr. ab uno disce omnes[Lat].

     #16a. [Absence or want of uniformity.] Nonuniformity. -- N. diversity,
irregularity, unevenness; multiformity &c. 81; unconformity &c. 83;
roughness &c. 256; dissimilarity, dissimilitude, divarication, divergence.
     Adj. diversified  varied, irregular, uneven,  rough &c. 256;
multifarious; multiform &c. 81; of various kinds; all manner of, all sorts
of, all kinds of.
     Adv. variously, in all manner of ways, here there and everywhere.

%
     3. PARTIAL RELATION
%

     #17. Similarity. -- N. similarity, resemblance, likeness, similitude,
semblance; affinity, approximation, parallelism; agreement &c. 23; analogy,
analogicalness[obs3]; correspondence, homoiousia[obs3], parity.
     connaturalness[obs3], connaturality[obs3]; brotherhood, family
likeness.
     alliteration, rhyme, pun.     
     repetition &c. 104; sameness &c. (identity) 13; uniformity &c. 16;
isogamy[obs3].
     analogue; the like; match, pendant, fellow companion, pair, mate,
twin, double, counterpart, brother, sister; one's second self, alter ego,
chip of the old block, par nobile fratrum[Lat], Arcades ambo[obs3], birds
of a feather, et hoc genus omne[Lat]; gens de meme famille[Fr].
     parallel; simile; type &c. (metaphor) 521; image &c. (representation)
554; photograph; close resemblance, striking resemblance, speaking
resemblance, faithful likeness,  faithful resemblance.
     V. be similar &c. adj.; look like, resemble, bear resemblance;  smack
of, savor of,; approximate; parallel, match, rhyme with; take after;
imitate &c. 19; favor, span [U. S.].
     render similar &c. adj.; assimilate, approximate, bring near;
connaturalize[obs3], make alike; rhyme, pun.
     Adj. similar; resembling &c. v.; like, alike; twin.
     analogous, analogical; parallel, of a piece[Fr]; such as, so;
homoiousian[obs3].
     connatural[obs3],  congener, allied to; akin to &c. (consanguineous) 1
1.
     approximate, much the same, near, close, something like, sort of, in
the ballpark, such like; a show of; mock, pseudo, simulating, representing.
     exact &c. (true) 494; lifelike, faithful; true to nature, true to
life, the very image, the very picture of; for all the world like, comme
deux gouttes d'eau[Fr]; as like as two peas in a pod, as like as it can
stare; instar omnium[Lat], cast in the same mold, ridiculously like.
     Adv. as if, so to speak; as it were, as if it were; quasi, just as,
veluti in speculum[Lat].
     Phr. et sic de similibus[Lat]; tel maitre tel valet[Fr]; tel pere tel
fils[Fr]; like master, like servant; like father, like son; the fruit
doesn't fall far from the tree; a chip off the old block


<--  p.  6  -->


     #18. Dissimilarity. -- N. dissimilarity, dissimilaritude[obs3];
unlikeness, diversity, disparity, dissemblance[obs3]; divergence,
variation.; difference &c. 15; novelty, originality; creativeness;
oogamy[obs3].
     V. be unlike &c. adj.; vary &c. (differ) 15; bear no resemblance to,
differ toto coelo[Lat].
     render unlike &c. adj.; vary &c. (diversify) 140.
     Adj. dissimilar, unlike, disparate; divergent; of a different kind &c.
(class) 75 unmatched, unique; new, novel; unprecedented &c. 83; original.
     nothing of the kind; no such thing, quite another thing; far from it,
cast in a different mold, tertium quid[Lat], as like a dock as a daisy,
"very like a whale " [Hamlet]; as different as chalk from cheese,  as
different as Macedon and Monmouth; lucus a non lucendo[Lat].
     diversified &c. 16a.
     Adv. otherwise.
     Phr. diis aliter visum[Lat]; " no more like my father than I to
Hercules" [Hamlet].

     #19. Imitation. -- N. imitation; copying &c. v.; transcription;
repetition, duplication, reduplication; quotation; reproduction;
mimeograph, xerox, facsimile; reprint, offprint.
     mockery, mimicry; simulation, impersonation, personation;
representation &c. 554; semblance; copy &c. 21; assimilation.
     paraphrase, parody, take-off, lampoon, caricature  &c. 21.
     plagiarism; forgery, counterfeit &c. (falsehood) 544; celluloid.
     imitator, echo, cuckoo|, parrot, ape, monkey, mocking bird, mime;
copyist, copycat; plagiarist, pirate.
     V. imitate, copy, mirror, reflect, reproduce, repeat; do like, echo,
reecho, catch; transcribe;  match, parallel.
     mock, take off, mimic, ape, simulate, impersonate, personate; act &c.
(drama) 599; represent &c. 554; counterfeit, parody, travesty, caricature,
lampoon, burlesque.
     follow in the steps of, tread in the steps,  follow in the footsteps
of, follow in the wake of; take pattern by; follow suit,  follow the
example of; walk in the shoes of, take a leaf out of another's book, strike
in with, follow suit; take after, model after; emulate.
     Adj. imitated &c. v.; mock, mimic; modelled after, molded on.
     paraphrastic; literal; imitative; secondhand; imitable; aping, apish,
mimicking.

     Adv. literally, to the letter, verbatim, literatim[Lat], sic, totidem
verbis[Lat], word for word, mot a mot[Fr]; exactly, precisely.

     Phr.like master like man; " like - but oh! how different! "
[Wordsworth]; " genius borrows nobly " [Emerson]; " pursuing echoes calling
'mong the rocks " [A. Coles]; " quotation confesses inferiority "
[Emerson]; "Imitation is the sincerest form of flattery".


     #20. Nonimitation. -- N. no imitation; originality; creativeness.
     invention, creation.
     Adj. unimitated[obs3], uncopied[obs3]; unmatched, unparalleled;
inimitable &c. 13; unique, original; creative, inventive, untranslated;
exceptional, rare, sui generis uncommon[Lat], unexampled.


     #20a. Variation. -- N. variation; alteration &c. (change) 140.
modification, moods and tenses; discrepance[obs3], discrepancy.
divergency &c. 291[obs3]; deviation &c. 279; aberration; innovation.
V. vary &c. (change) 140; deviate &c. 279; diverge &c. 291; alternate,
swerve.
Adj. varied &c. v.; modified; diversified &c. 16a.

     #21. [Result of imitation.] Copy. -- N. copy, facsimile, counterpart,
effigies, effigy, form, likeness.
     image, picture, photo,  xerox, similitude, semblance, ectype[obs3],
photo offset, electrotype; imitation &c. 19; model, representation,
adumbration, study; portrait &c. (representation) 554; resemblance.
     duplicate, reproduction; cast, tracing; reflex, reflexion[Brit],
reflection; shadow, echo.
      transcript[copy into a non-visual form], transcription; recording,
scan.
     chip off the old block; reprint, new printing; rechauffe[Fr];
apograph[obs3], fair copy.
     parody, caricature, burlesque, travesty, travestie[obs3], paraphrase.
     [copy with some differences] derivative, derivation, modification,
expansion, extension, revision; second edition &c. (repetition) 104.
     servile copy, servile imitation; plagiarism, counterfeit, fake
&c.(deception) 545; pasticcio[obs3].
     Adj. faithful; lifelike &c. (similar) 17; close, conscientious.
     unoriginal, imitative, derivative.

     #22. [Thing copied.] Prototype. -- N. prototype, original, model,
pattern, precedent, standard, ideal, reference, scantling, type; archetype,
antitype[obs3]; protoplast, module, exemplar, example, ensample[obs3],
paradigm; lay-figure.
     text, copy, design; fugleman[obs3], keynote. die, mold; matrix, last,
plasm[obs3]; proplasm[obs3], protoplasm; mint; seal, punch, intaglio,
negative; stamp.
     V. be an example, be a role model, set an example; set a copy. Phr. a
precedent embalms a principle [Disraeli]; exempla sunt odiosa[Lat].

<--  p.  7  -->

%
     4. GENERAL RELATION
%

     #23. Agreement. -- N. agreement; accord, accordance; unison, harmony;
concord &c. 714; concordance, concert; understanding, mutual understanding.
     conformity &c. 82; conformance; uniformity &c. 16; consonance,
consentaneousness[obs3], consistency; congruity, congruence; keeping;
congeniality; correspondence, parallelism, apposition, union.
     fitness, aptness &c. adj.; relevancy; pertinence, pertinencey[obs3];
sortance|; case in point; aptitude, coaptation[obs3], propriety,
applicability, admissibility, commensurability, compatibility; cognation
&c. (relation) 9.
     adaption[obs3], adjustment, graduation, accommodation; reconciliation,
reconcilement; assimilation.
     consent &c. (assent) 488; concurrence &c. 178; cooperation &c. 709.
     right man in the right place, very thing,; quite the thing, just the
thing.
     V. be accordant &c. adj.; agree, accord, harmonize; correspond, tally,
respond; meet, suit, fit, befit, do, adapt itself to; fall in with, chime
in with, square with, quadrate with, consort with, comport with; dovetail,
assimilate; fit like a glove, fit to a tittle, fit to a T; match &c. 17;
become one; homologate[obs3].
     consent &c. (assent) 488.
     render accordant &c. adj.; fit, suit, adapt, accommodate; graduate;
adjust &c. (render, equal) 27; dress, regulate, readjust; accord,
harmonize,. reconcile; fadge[obs3], dovetail, square.
     Adj. agreeing, suiting &c. v.; in accord, accordant, concordant,
consonant, congruous, consentaneous[obs3], correspondent, congenial;
coherent; becoming; harmonious reconcilable, conformable; in accordance
with, in harmony with, in keeping with, in unison with, &c. n.; at one
with, of one mind, of a piece[Fr]; consistent, compatible, proportionate;
commensurate; on all fours.
     apt, apposite, pertinent, pat; to the point, to the purpose; happy,
felicitous, germane, ad rem[Lat], in point, on point, directly on point,
bearing upon, applicable, relevant, admissible.
     fit adapted, in loco, a propos[Fr], appropriate, seasonable, sortable,
suitable, idoneous[obs3], deft; meet &c. (expedient) 646.

     at home, in one's proper element.
     Adv. a propos of[Fr]; pertinently &c. adj.
     Phr. rem acu tetigisti[Lat][obs3]; if the shoe fits, wear it; the cap
fits; auxilia humilia firma consensus facit [Lat][Syrus]; discers concordia
[Lat][Ovid].

<--  p.  8  -->



     #24. Disagreement. -- N. disagreement; discord, discordance;
dissonance, dissidence, discrepancy; unconformity &c. 83; incongruity,
incongruence[obs3]; discongruity[obs3], mesalliance; jarring &c. v.;
dissension &c. 713; conflict &c. (opposition) 708; bickering, clashing,
misunderstanding, wrangle.
     disparity, mismatch, disproportion; dissimilitude, inequality;
disproportionateness &c. adj[obs3].; variance, divergence, repugnance.
     unfitness &c. adj.; inaptitude, impropriety; inapplicability &c. adj.;
inconsistency, inconcinnity[obs3]; irrelevancy &c. (irrelation) 10[obs3].
     misjoining[obs3], misjoinder[obs3]; syncretism[obs3], intrusion,
interference; concordia discors[Lat].
     fish out of water.
     V. disagree; clash, jar &c. (discord) 713; interfere, intrude, come
amiss; not concern &c. 10; mismatch; humano capiti cervicem jungere
equinam[Lat].
     Adj. disagreeing &c. v.; discordant, discrepant; at variance, at war;
hostile, antagonistic, repugnant, incompatible, irreconcilable,
inconsistent with; unconformable, exceptional &c. 83; intrusive,
incongruous; disproportionate, disproportionated[obs3]; inharmonious,
unharmonious[obs3]; inconsonant, unconsonant[obs3]; divergent, repugnant
to.
     inapt, unapt, inappropriate, improper; unsuited, unsuitable;
inapplicable, not to the point; unfit, unfitting, unbefitting; unbecoming;
illtimed, unseasonable, mal a propos[Fr], inadmissible; inapposite &c.
(irrelevant) 10. uncongenial; ill-assorted, ill-sorted; mismatched,
misjoined[obs3], misplaced, misclassified; unaccommodating, irreducible,
incommensurable, uncommensurable[obs3]; unsympathetic.
     out of character,  out of keeping, out of proportion,  out of joint,
out of tune,  out of place,  out of season,  out of its element; at odds
with, at variance with.
     Adv. in defiance, in contempt,in spite of; discordantly &c. adj.; a
tort et a travers[obs3].
     Phr. asinus ad lyram[Lat].
%
SECTION III. QUANTITY

1. SIMPLE QUANTITY
%
     #25. [Absolute quantity.] Quantity. -- N. quantity, magnitude; size
&c. (dimensions) 192; amplitude, magnitude, mass, amount, sum, quantum,
measure, substance, strength, force.
     [Science of quantity.] mathematics, mathesis[obs3].
     [Logic.] category, general conception, universal predicament.
     [Definite or finite quantity.] armful, handful, mouthful, spoonful,
capful; stock, batch, lot, dose; yaffle[obs3].
     V. quantify, measure, fix, estimate, determine, quantitate, enumerate.
     Adj. quantitative, some, any, aught, more or less, a few.
     Adv.  to the tune of, all of,  a full, the sum of, fully, exactly,
precisely.



     #26. [Relative quantity.] Degree. -- N. degree, grade, extent,
measure, amount, ratio, stint, standard, height, pitch; reach, amplitude,
range, scope, caliber; gradation, shade; tenor, compass; sphere, station,
rank, standing; rate, way, sort.
     point, mark, stage &c. (term) 71; intensity, strength &c. (greatness)
31.
     Adj. comparative; gradual, shading off; within the bounds &c. (limit)
233.
     Adv. by degrees, gradually, inasmuch, pro tanto[It]; however,
howsoever; step by step, bit by bit, little by little, inch by inch, drop
by drop; a little at a time, by inches, by slow degrees, by degrees, by
little and little; in some degree, in some measure; to some extent; di
grado in grado[Lat].
%
2. COMPARATIVE QUANTITY
%

     #27. [Sameness of quantity or degree.] Equality. -- N. equality,
parity, coextension[obs3], symmetry, balance, poise; evenness, monotony,
level.
     equivalence; equipollence[obs3], equipoise, equilibrium,
equiponderance[obs3]; par, quits, a wash; not a pin to choose; distinction
without a difference, six of one and half a dozen of the other; tweedle dee
and tweedle dum[Lat]; identity &c. 13; similarity &c. 17.
     equalization, equation; equilibration, co*ordination, adjustment,
readjustment. drawn game, drawn battle; neck and neck race; tie, draw,
standoff, dead heat.
     match, peer, compeer, equal, mate, fellow, brother; equivalent.
     V. be equal &c. adj.; equal, match,reach, keep pace with, run abreast;
come to, amount to, come up to; be on a level with, lie on a level with;
balance; cope with; come to the same thing.
     render equal &c. adj.; equalize level, dress, balance, equate,
handicap, give points, spot points, handicap, trim, adjust, poise; fit,
accommodate; adapt &c. (render accordant) 23; strike a balance; establish
equality, restore equality, restore equilibrium; readjust; stretch on the
bed of Procrustes.
     Adj. equal, even, level, monotonous, coequal, symmetrical, coordinate;
on a par with,  on a level with, on a footing with; up to the mark;
equiparant[obs3].
     equivalent, tantamount; indistinguishable; quits; homologous;
synonymous &c. 522; resolvable into, convertible, much at one, as broad as
long, neither more nor less.; much the same as, the same thing as, as good
as; all one, all the same; equipollent, equiponderant[obs3],
equiponderous[obs3], equibalanced[obs3]; equalized &c. v.; drawn; half and
half; isochronal, isochronous isoperimetric[obs3], isoperimetrical[obs3];
isobath[Oceanography], isobathic[Oceanography].
     Adv. equally &c. adj.; pari passu[Lat], ad eundum[Lat], caeteris
paribus[Lat]; in equilibrio[Lat]; to all intents and purposes.

     Phr. it comes to the same thing,  it amounts to the same thing; what
is sauce for the goose is sauce for the gander.



     #28. [Difference of quantity or degree.] Inequality. -- N. inequality;
disparity, imparity; odds; difference &c. 15; unevenness; inclination of
the balance, partiality, bias, weight; shortcoming; casting weight, make-
weight; superiority &c. 33; inferiority &c. 34; inequation[obs3].
     V. be unequal &c. adj.; countervail; have the advantage, give the
advantage; turn the scale; kick the beam; topple,topple over; overmatch &c.
33; not come up to &c. 34.
     Adj. unequal, uneven, disparate, partial; unbalanced, overbalanced;
top-heavy, lopsided, biased, skewed; disquiparant[obs3].
     Adv. haud passibus aequis  [Latin][Vergil].


<--  p.  9  -->

     #29. Mean. -- N. mean, average; median, mode; balance,  medium,
mediocrity, generality;  golden mean &c. (mid-course) 628; middle &c. 68;
compromise &c. 774; middle course, middle state; neutrality.
     mediocrity, least common denominator.
     V. split the difference; take the average &c. n.; reduce to a mean &c.
n.; strike a balance, pair off.
Adj. mean, intermediate; middle &c. 68; average; neutral.
     mediocre, middle-class; commonplace &c. (unimportant) 643.
     Adv. on an average, in the long run; taking one with another, taking
all things together, taking it for all in all; communibus annis[Lat], in
round numbers.
     Phr. medium tenuere beati[Lat].

     #30. Compensation. -- N. compensation, equation; commutation;
indemnification; compromise &c. 774 neutralization, nullification;
counteraction &c. 179; reaction; measure for measure. retaliation &c. 718
equalization &c. 27; robbing Peter to pay Paul.
     set-off, offset; make-weight, casting-weight; counterpoise, ballast;
indemnity, equivalent, quid pro,quo; bribe, hush money; amends &c.
(atonement) 952; counterbalance,  counterclaim;  cross-debt, cross-demand.
     V. make compensation; compensate, compense[obs3]; indemnify;
counteract, countervail, counterpoise; balance; outbalance[obs3],
overbalance, counterbalance; set off; hedge, square, give and take; make up
for, lee way; cover, fill up, neutralize, nullify; equalize &c. 27; make
good; redeem &c. (atone) 952.
     Adj. compensating, compensatory; countervailing &c. v.; in the
opposite scale; equivalent &c. (equal) 27.
     Adv. in return, in consideration; but, however, yet, still,
notwithstanding; nevertheless, nathless[obs3], none the less; although,
though; albeit, howbeit; mauger[obs3]; at all events, at any rate; be that
as it may, for all that, even so, on the other, hand, at the same time,
quoad minus[Lat], quand meme[Fr], however that may be; after all is said
and done; taking one thing with another &c. (average) 29.
     Phr. " light is mingled with the gloom " [Whittier]; every dark cloud
has a silver lining; primo avulso non deficit alter [Lat][obs3][Vergil];
saepe creat molles aspera spina rosas [Lat][Ovid].
%
          QUANTITY BY COMPARISON WITH A STANDARD
%
     #31. Greatness. -- N. greatness &c. adj.; magnitude; size &c.
(dimensions) 192; multitude &c. (number) 102; immensity; enormity; infinity
&c. 105; might, strength, intensity, fullness; importance &c. 642.
     great quantity, quantity, deal, power, sight, pot, volume, world;
mass, heap &c. (assemblage) 72; stock &c. (store) 636; peck, bushel, load,
cargo; cartload[obs3], wagonload, shipload; flood, spring tide; abundance
&c. (sufficiency) 639.
     principal part, chief part, main part, greater part, major part, best
part, essential part ; bulk, mass &c. (whole) 50.
     V. be great &c. adj.; run high, soar, tower, transcend; rise to a
great height, carry  to a great height; know no bounds; ascend, mount.
     enlarge &c. (increase) 35, (expand) 194.
     Adj. great; greater &c. 33; large, considerable, fair, above par; big,
huge &c. (large in size) 192; Herculean, cyclopean; ample; abundant &c.
(enough) 639 full, intense, strong, sound, passing, heavy, plenary, deep,
high; signal, at its height, in the zenith.
     world-wide, widespread, far-famed, extensive; wholesale; many &c. 102.
     goodly, noble, precious, mighty; sad, grave, heavy, serious; far gone,
arrant, downright; utter, uttermost; crass, gross, arch, profound, intense,
consummate; rank, uninitiated, red-hot, desperate; glaring, flagrant, stark
staring; thorough-paced, thoroughgoing; roaring, thumping; extraordinary.;
important &c. 642; unsurpassed &c. (supreme) 33; complete &c. 52. august,
grand, dignified, sublime, majestic &c. (repute) 873.
     vast, immense, enormous, extreme; inordinate, excessive, extravagant,
exorbitant, outrageous, preposterous, unconscionable, swinging, monstrous,
overgrown; towering, stupendous, prodigious, astonishing, incredible;
marvelous &c.
870.
     unlimited &c. (infinite) 105; unapproachable, unutterable,
indescribable, ineffable, unspeakable, inexpressible, beyond expression,
fabulous.
     undiminished, unabated, unreduced[obs3], unrestricted.
     absolute, positive, stark, decided, unequivocal, essential, perfect,
finished.
     remarkable, of mark, marked, pointed, veriest; noteworthy; renowned.
     Adv.  truly &c. (truth) 494[in a positive degree]; decidedly,
unequivocally, purely, absolutely, seriously, essentially, fundamentally,
radically, downright, in all conscience; for the most part, in the main.
     [in a complete degree] entirely &c. (completely) 52; abundantly &c.
(sufficiently) 639; widely, far and wide.
     [in a great or high degree] greatly &c. adj.; much, muckle[obs3],
well, indeed, very, very much, a deal, no end of, most, not a little;
pretty, pretty well; enough, in a great measure, richly; to a large extent,
to a great extent, to a gigantic extent; on a large scale; so; never so,
ever so; ever so dole; scrap, shred, tag, splinter, rag, much; by
wholesale; mighty, powerfully; with a witness, ultra[Lat], in the extreme,
extremely, exceedingly, intensely, exquisitely, acutely, indefinitely,
immeasurably; beyond compare, beyond comparison, beyond measure, beyond all
bounds; incalculably, infinitely.
     [in a supreme degree] preeminently, superlatively &c. (superiority)
33.
     [in a too great degree] immoderately, monstrously, preposterously,
inordinately, exorbitantly, excessively, enormously, out of all proportion,
with a vengeance.
     [in a marked degree] particularly, remarkably, singularly, curiously,
uncommonly, unusually, peculiarly, notably, signally, strikingly,
pointedly, mainly, chiefly; famously, egregiously, prominently, glaringly,
emphatically, <gr/kat exochin/>[Grl], strangely, wonderfully, amazingly,
surprisingly, astonishingly, incredibly, marvelously, awfully,
stupendously.
     [in an exceptional degree] peculiarly &c. (unconformity) 83.
     [in a violent degree] furiously &c. (violence) 173; severely,
desperately, tremendously, extravagantly, confoundedly, deucedly,
devilishly, with a vengeance; a outrance[obs3], a toute outrance[Fr][obs3].
     [in a painful degree] painfully, sadly, grossly, sorely, bitterly,
piteously, grievously, miserably, cruelly, woefully, lamentably,
shockingly, frightfully, dreadfully, fearfully, terribly, horribly.
     Phr. a maximis ad minima[Lat]; " greatness knows itself" [Henry IV]; "
mightiest powers by deepest calms are fed " [B. Cornwall]; minimum decet
libere cui multum licet [Lat][Seneca]; " some are born great, some achieve
greatness, and some have greatness thrust upon them " [Twelfth Night].



<--   p.  10  -->
<-- to a limited degree should be broken out to a section near to
qualification 469  -->

     #32. Smallness. -- N. smallness &c. adj.; littleness &c. (small size)
193; tenuity; paucity; fewness &c (small number) 103; meanness,
insignificance (unimportance) 643; mediocrity, moderation.
     small quantity, modicum, trace, hint, minimum; vanishing point;
material point, atom, particle, molecule, corpuscle, point, speck, dot,
mote, jot, iota, ace; minutiae, details; look, thought, idea, soupcon, dab,
dight[obs3], whit, tittle, shade, shadow; spark, scintilla, gleam; touch,
cast; grain, scruple, granule, globule, minim, sup, sip, sop, spice, drop,
droplet, sprinkling, dash, morceau[obs3], screed, smack, tinge, tincture;
inch, patch, scantling, tatter, cantlet[obs3], flitter, gobbet[obs3], mite,
bit, morsel, crumb, seed, fritter, shive[obs3]; snip, snippet; snick[obs3],
snack, snatch, slip, scrag[obs3]; chip, chipping; shiver, sliver, driblet,
clipping, paring, shaving, hair.
     nutshell; thimbleful, spoonful, handful, capful, mouthful; fragment;
fraction &c. (part) 51; drop in the ocean.
     animalcule &c. 193.
     trifle &c. (unimportant thing) 643; mere nothing, next to nothing;
hardly anything; just enough to swear by; the shadow of a shade.
     finiteness, finite quantity.
     V. be small &c. adj.; lie in a nutshell.
     diminish &c. (decrease) 36; (contract) 195.
     Adj. small, little; diminutive &c. (small in size) 193; minute; fine;
inconsiderable, paltry &c. (unimportant) 643; faint &c. (weak) 160;
slender, light, slight, scanty, scant, limited; meager &c. (insufficient)
640; sparing; few &c. 103; low, so-so, middling, tolerable, no great
shakes; below par, under par, below  the mark; at a low ebb; halfway;
moderate, modest; tender, subtle.
     inappreciable, evanescent, infinitesimal, homeopathic, very small;
atomic, corpuscular, microscopic, molecular, subatomic.
     mere, simple, sheer, stark, bare; near run.
     dull, petty, shallow, stolid, ungifted, unintelligent.
     Adv.  to a small extent[in a small degree], on a small scale; a little
bit, a wee bit; slightly &c. adj.; imperceptibly; miserably, wretchedly;
insufficiently &c. 640; imperfectly; faintly &c. 160; passably, pretty
well, well enough.
     [in a certain or limited degree] partially, in part; in a certain
degree, to a certain degree; to a certain extent; comparatively; some,
rather in some degree, in some measure; something, somewhat; simply, only,
purely, merely; at least, at the least, at most, at the most; ever so
little, as little as may be, tant soit peu[Fr], in ever so small a degree;
thus far, pro  tanto[It], within bounds, in a manner, after a fashion, so
to speak.
     almost, nearly, well-nigh, short of, not quite, all but; near upon,
close upon; peu s'en faut[Fr], near the mark; within an ace of, within an
inch of; on the brink of; scarcely, hardly, barely, only just, no more
than.  about[in an uncertain degree], thereabouts, somewhere about, nearly,
say; be the same,  be little more or less.  no ways[in no degree], no way,
no wise; not at all, not in the least, not a bit, not a bit of it, not a
whit, not a jot, not a shadow; in no wise, in no respect; by no means, by
no manner of means; on no account, at no hand.
Phr. dare pondus idonea fumo [Lat][Persius]; magno conatu magnas nugas
[Lat][Terence]; " small sands the mountain, moments make the year "
[Young].

<--  p.  11  -->
%

     QUANTITY BY COMPARISON WITH A SIMILAR OBJECT
%

     #33. Superiority. [Supremacy.] -- N. superiority, majority; greatness
&c. 31; advantage; pull; preponderance, preponderation; vantage ground,
prevalence, partiality; personal superiority; nobility &c. (rank) 875;
Triton among the minnows, primus inter pares[Lat], nulli secundus[Lat],
captain; crackajack * [obs3][U. S.].
     supremacy, preeminence; lead; maximum; record; <gr/trikumia/>[obs3],
climax; culmination &c. (summit) 210; transcendence; ne plus ultra[Lat];
lion's share, Benjamin's mess; excess, surplus &c. (remainder) 40;
(redundancy) 641.
     V. be superior &c. adj.; exceed, excel, transcend; outdo,
outbalance[obs3], outweigh, outrank, outrival, out-Herod; pass, surpass,
get ahead of; over-top, override, overpass, overbalance, overweigh,
overmatch; top, o'ertop, cap, beat, cut out; beat hollow; outstrip &c. 303;
eclipse, throw into the shade, take the shine out of, outshine, put one's
nose out of joint; have the upper hand, have the whip hand of, have the
advantage; turn the scale, kick the beam; play first fiddle &c.
(importance) 642,; preponderate, predominate, prevail; precede, take
precedence, come first; come to a  head, culminate; beat &c. all others,
bear the palm; break the record; take the cake * [U. S.].
become larger, render larger &c. (increase) 35, (expand) 194.
     Adj. superior, greater, major, higher; exceeding &c. v.;great &c. 31;
distinguished, ultra[Lat]; vaulting; more than a match for.
     supreme, greatest, utmost, paramount, preeminent, foremost, crowning;
first-rate &c. (important) 642, (excellent) 648; unrivaled peerless,
matchless; none such, second to none, sans pareil[Fr]; unparagoned[obs3],
unparalleled, unequalled, unapproached[obs3], unsurpassed; superlative,
inimitable facile princeps[Lat], incomparable, sovereign, without parallel,
nulli secundus[Lat], ne plus ultra[Lat]; beyond compare, beyond comparison;
culminating &c. (topmost) 210; transcendent, transcendental;plus royaliste
que le Roi[Fr], more catholic than the Pope
     increased &c. (added to) 35; enlarged &c. (expanded) 194.
     Adv. beyond, more, over; over the mark, above the mark; above par;
upwards of, in advance of; over and above; at the top of the scale, at its
height.
     [in a superior or supreme degree] eminently, egregiously,
preeminently, surpassing, prominently, superlatively, supremely, above all,
of all things, the most, to crown all, <gr/kat exochin/gr>[Grl], par
excellence, principally, especially, particularly, peculiarly, a fortiori,
even, yea, still more.

Phr. " I shall not look upon his like again " [Hamlet]; deos fortioribus
addesse [Lat][Tacitus].

<--  p.  12 -->


     #34. Inferiority. -- N. inferiority, minority, subordinacy;
shortcoming, deficiency; minimum; smallness &c. 32; imperfection; lower
quality, lower worth.
     [personal inferiority] commonalty &c. 876.
     V. be inferior &c. adj.; fall short of, come short of;  not pass, not
come up to; want.
     become smaller, render smaller &c. (decrease) 36, (contract) 195; hide
its diminished head, retire into the shade, yield the palm, play second
fiddle, be upstaged, take a back seat.
     Adj. inferior, smaller; small &c. 32; minor, less, lesser, deficient,
minus, lower, subordinate, secondary; secondrate &c. (imperfect) 651; sub,
subaltern; thrown into the shade; weighed in the balance and found wanting;
not fit to hold a candle to, can't hold a candle to.
     least, smallest &c. (see little, small &c. 193); lowest.
     diminished &c. (decreased) 36; reduced &c. (contracted) 195;
unimportant &c. 643.
Adv. less; under the mark, below the mark,below par; at the bottom of the
scale, at a low  ebb, at a disadvantage; short of, under.

%
CHANGES IN QUANTITY
%

     #35. Increase. -- N. increase, augmentation, enlargement, extension;
dilatation &c. (expansion) 194; increment, accretion; accession &c. 37;
development, growth; aggrandizement, aggravation; rise; ascent &c. 305;
exaggeration exacerbation; spread &c. (dispersion) 73; flood tide; gain,
produce, product, profit.
     V. increase, augment, add to, enlarge;. dilate &c. (expand) 194; grow,
wax, get ahead. gain strength; advance; run up, shoot up; rise; ascend &c.
305; sprout &c. 194.
     aggrandize; raise, exalt; deepen, heighten; strengthen; intensify,
enhance, magnify, redouble; aggravate, exaggerate; exasperate, exacerbate;
add fuel to the flame, oleum addere camino[Lat], superadd &c. (add)
37[obs3]; spread &c. (disperse) 73.
     Adj. increased &c. v.; on the increase, undiminished; additional &c.
(added) 37.
     Adv. crescendo.
     Phr. vires acquirit eundo [Lat][Vergil].


     #36. Nonincrease,  Decrease. -- N. decrease, diminution; lessening &c.
v.; subtraction &c. 38; reduction, abatement, declension; shrinking &c.
(contraction.) 195; coarctation|; abridgment &c. (shortening) 201;
extenuation.
     subsidence, wane, ebb, decline; ebbing; descent &c. 306; decrement,
reflux, depreciation; deterioration &c. 659; anticlimax; mitigation &c.
(moderation) 174.
     V. decrease, diminish, lessen; abridge &c. (shorten) 201; shrink &c.
(contract) 195; drop off, fall off, tail off; fall away, waste, wear; wane,
ebb, decline; descend &c. 306; subside; melt away, die away; retire into
the shade, hide its diminished head, fall to a low ebb, run low, languish,
decay, crumble.
     bate, abate, dequantitate|; discount; depreciate; extenuate, lower,
weaken, attenuate, fritter away; mitigate &c. (moderate) 174; dwarf, throw
into the shade; reduce &c. 195; shorten &c. 201; subtract &c. 38.
Adj. unincreased &c. (see increase &c.35)[obs3]; decreased &c. v.;
decreasing &c. v.; on the wane &c. n.
     Phr. " a gilded halo hovering round decay " [Byron]; " fine by degrees
and beautifully less " [Prior].

<--  p.  13  -->

               3. CONJUNCTIVE QUANTITY

     #37. Addition. -- N. addition, annexation, adjection[obs3]; junction
&c. 43; superposition, superaddition, superjunction[obs3], superfetation;
accession, reinforcement; increase &c. 35; increment, supplement;
accompaniment &c. 88; interposition &c. 228; insertion &c. 300.
     V. add, annex, affix, superadd[obs3], subjoin, superpose; clap on,
saddle on; tack to, append, tag; ingraft[obs3]; saddle with; sprinkle;
introduce &c. (interpose) 228; insert &c. 300.
become added, accrue; advene[obs3], supervene.
     reinforce, reenforce, restrengthen[obs3]; swell the ranks of; augment
&c. 35.
     Adj. added &c. v.; additional; supplemental, supplementary;
suppletory[obs3], subjunctive; adjectitious[obs3], adscititious[obs3],
ascititious[obs3]; additive, extra, accessory.
     Adv. au reste[Fr], in addition, more, plus, extra; and, also,
likewise, too, furthermore, further, item; and also, and eke; else,
besides, to boot, et cetera; &c.; and so on, and so forth; into the
bargain, cum multis aliis[Lat], over and above, moreover.
     with, withal; including, inclusive, as well as, not to mention, let
alone; together with, along with, coupled with, in conjunction with;
conjointly; jointly &c. 43.
Phr. adde parvum parvo magnus acervus erit[Lat].



     #38. Nonaddition. Subtraction. - N. subtraction, subduction|!;
deduction, retrenchment; removal, withdrawal; ablation, sublation[obs3];
abstraction &c. (taking) 789; garbling,, &c. v. mutilation,
detruncation[obs3]; amputation; abscission, excision, recision; curtailment
&c. 201; minuend, subtrahend; decrease &c. 36; abrasion.
     V. subduct, subtract; deduct, deduce; bate, retrench; remove,
withdraw, take from, take away; detract.
     garble, mutilate, amputate, detruncate[obs3]; cut off, cut away, cut
out; abscind[obs3], excise; pare, thin, prune, decimate; abrade, scrape,
file; geld, castrate; eliminate.
     diminish &c. 36; curtail &c. (shorten) 201; deprive of &c. (take) 789;
weaken.
     Adj. subtracted &c. v.; subtractive.
     Adv. in deduction &c. n.; less; short of; minus, without, except,
except for, excepting, with the exception of, barring, save, exclusive of,
save and except, with a reservation; not counting, if one doesn't count.



     #39. [Thing added] Adjunct. -- N. adjunct; addition, additament[obs3];
additum[Lat], affix, appelidage[obs3], annexe[obs3], annex; augment,
augmentation; increment, reinforcement, supernumerary, accessory, item;
garnish, sauce; accompaniment &c. 88; adjective, addendum; complement,
supplement; continuation.
     rider, offshoot, episode, side issue, corollary; piece[Fr]; flap,
lappet, skirt, embroidery, trappings, cortege; tail, suffix &c. (sequel)
65; wing.
     Adj. additional &c. 37. alate[obs3], alated[obs3]; winged.
     Adv. in addition &c. 37.


     #40. [Thing remaining.] Remainder. -- N.
     remainder, residue; remains, remanent, remnant, rest, relic; leavings,
heeltap[obs3], odds and ends, cheesepairings[obs3], candle ends,
orts[obs3]; residuum; dregs &c. (dirt) 653; refuse &c. (useless) 645;
stubble, result, educt[obs3]; fag-end; ruins, wreck, skeleton., stump;
alluvium.
     surplus, overplus[obs3], excess; balance, complement; superplus[obs3],
surplusage[obs3]; superfluity &c.(redundancy) 641; survival,
survivance[obs3].
     V.  remain,; be left &c. adj.; exceed, survive; leave.



Adj.remaining, left; left behind  left over; residual, residuary; over,
odd; unconsumed, sedimentary; surviving; net; exceeding, over and above;
outlying, outstanding; cast off &c. 782; superfluous &c. (redundant) 641.


     #40a. [Thing deducted.] Decrement. -- N. decrement, discount, defect,
loss, deduction; afterglow; eduction[obs3]; waste.

<--  p.  14  -->


     #41. [Forming a whole without coherence.] Mixture. -- N. mixture,
admixture,  commixture, commixtion[obs3]; commixion[obs3], intermixture,
alloyage[obs3], matrimony; junction &c. 43; combination &c. 48;
miscegenation.
     impregnation; infusion, diffusion suffusion, transfusion;
infiltration; seasoning, sprinkling, interlarding; interpolation &c. 228
adulteration, sophistication.
     [Thing mixed] tinge, tincture, touch, dash, smack, sprinkling, spice,
seasoning, infusion, soupcon.
     [Compound resulting from mixture] alloy, amalgam; brass,
chowchow[obs3], pewter; magma, half-and-half, melange, tertium quid[Lat],
miscellany, ambigu|, medley, mess, hotchpot[obs3], pasticcio[obs3],
patchwork, odds and ends, all sorts; jumble &c. (disorder) 59; salad,
sauce, mash, omnium gatherum[Lat], gallimaufry, olla-podrida[obs3], olio,
salmagundi, potpourri, Noah's ark, caldron texture, mingled yarn; mosaic
&c. (variegation) 440.

     half-blood, half-caste. mulatto; terceron[obs3], quarteron[obs3],
quinteron &c.[obs3];.quadroon, octoroon; griffo[obs3], zambo[obs3];
cafuzo[obs3]; Eurasian; fustee[obs3], fustie[obs3]; griffe, ladino[obs3],
marabou, mestee[obs3], mestizo, quintroon, sacatra  zebrule[obs3][U. S.];
catalo[obs3]; cross, hybrid, mongrel.

     V. mix; join &c. 43; combine &c. 48; commix, immix[obs3], intermix;
mix up with, mingle; commingle, intermingle, bemingle[obs3]; shuffle &c.
(derange) 61; pound together; hash up, stir up; knead, brew; impregnate
with; interlard &c. (interpolate) 228; intertwine, interweave &c. 219;
associate with; miscegenate[obs3].
be mixed &c.; get among, be entangled with.
     instill,  imbue; infuse, suffuse, transfuse; infiltrate, dash, tinge,
tincture, season, sprinkle, besprinkle, attemper[obs3], medicate, blend,
cross; alloy, amalgamate, compound, adulterate, sophisticate, infect.

     Adj. mixed &c. v.; implex[obs3], composite, half-and-half, linsey-
woolsey, chowchow, hybrid, mongrel, heterogeneous; motley &c. (variegated)
440; miscellaneous, promiscuous, indiscriminate; miscible.
Adv. among, amongst, amid, amidst; with; in the midst of, in the crowd.

     #42. [Freedom from mixture.] Simpleness. -- N. simpleness &c. adj.;
purity, homogeneity.
     elimination; sifting &c. v.; purification &c. (cleanness) 652.
     V.  render simple &c. adj.; simplify.
     sift, winnow, bolt, eliminate; exclude, get rid of; clear; purify &c.
(clean) 652; disentangle &c. (disjoin)  44.
     Adj. simple, uniform, of a piece[Fr], homogeneous, single, pure,
sheer, neat.
     unmixed, unmingled[obs3], unblended, uncombined, uncompounded;
elementary, undecomposed; unadulterated, unsophisticated, unalloyed,
untinged[obs3], unfortified, pur et simple[Fr]; incomplex[obs3].
     free from, exempt from; exclusive.
     Adv. simple &c. adj. only.



     #43. Junction. -- N. junction; joining &c. v.; joinder[Law], union
connection, conjunction, conjugation; annexion[obs3], annexation,
annexment[obs3]; astriction[obs3], attachment, compagination[obs3],
vincture[obs3], ligation, alligation[obs3]; accouplement[obs3]; marriage
&c. (wedlock,) 903; infibulation[obs3], inosculation[obs3],
symphysis[Anat], anastomosis, confluence, communication, concatenation;
meeting, reunion; assemblage &c. 72.
     coition, copulation;sex, sexual congress,sexual conjunction, sexual
intercourse, love-making.
     joint, joining, juncture, pivot, hinge, articulation,
commissure[obs3], seam, gore, gusset, suture, stitch; link &c. 45; miter
mortise.
     closeness, tightness, &c. adj.; coherence &c. 46; combination &c. 48.
     annexationist.
     V. join, unite; conjoin, connect; associate; put together, lay
together, clap together, hang together, lump together, hold together, piece
together[Fr], tack together, fix together, bind up together together;
embody, reembody[obs3]; roll into one.
     attach, fix, affix, saddle on, fasten, bind, secure, clinch, twist,
make fast &c. adj.; tie, pinion, string, strap, sew, lace, tat, stitch,
tack, knit, button, buckle, hitch, lash, truss, bandage, braid, splice,
swathe, gird, tether, moor, picket, harness, chain; fetter &c. (restrain)
751; lock, latch, belay, brace, hook, grapple, leash, couple,
accouple[obs3], link, yoke, bracket; marry &c. (wed) 903; bridge over,
span.
     braze; pin, nail, bolt, hasp, clasp, clamp, crimp, screw, rivet;
impact, solder, set; weld together, fuse together; wedge, rabbet, mortise,
miter, jam, dovetail, enchase[obs3]; graft, ingraft[obs3],
inosculate[obs3]; entwine, intwine[obs3]; interlink, interlace, intertwine,
intertwist[obs3], interweave; entangle; twine round, belay; tighten; trice
up, screw up.
     be joined &c.; hang together, hold together; cohere &c. 46.
     Adj. joined &c. v.; joint; conjoint, conjunct; corporate, compact;
hand in hand.
     firm, fast, close, tight, taut, taught, secure, set, intervolved |;
inseparable, indissoluble, insecable[obs3], severable.
     Adv. jointly &c. adj.; in conjunction with &c. (in addition to) 37;
fast, firmly, &c. adj.; intimately.
Phr. tria juncta in uno[Lat].

<--  p.  15  -->




     #44. Disjunction. -- N. disjunction, disconnection, disunity,
disunion, disassociation, disengagement; discontinuity &c. 70;
abjunction[obs3]; cataclasm[obs3]; inconnection[obs3]; abstraction,
abstractedness; isolation; insularity, insulation; oasis; island;
separateness  &c. adj.; severalty; disjecta membra[Lat]; dispersion &c. 73;
apportionment &c. 786.
     separation; parting &c. v.; circumcision; detachment, segregation;
divorce, sejunction|, seposition|, diduction[obs3], diremption[obs3],
discerption[obs3]; elision; caesura, break, fracture,
division, subdivision, rupture; compartition |; dismemberment,
dislocation; luxation[obs3]; severance, disseverance; scission; rescission,
abscission; laceration, dilaceration[obs3]; disruption, abruption[obs3];
avulsion[obs3], divulsion[obs3]; section, resection, cleavage; fission;
partibility[obs3], separability.

     fissure, breach, rent, split, rift, crack, slit, incision.
     dissection anatomy; decomposition &c. 49; cutting instrument &c
(sharpness) 253; buzzsaw, circular saw, rip saw.
     separatist.
     V. be disjoined &c.; come off, fall off, come to pieces, fall to
pieces; peel off; get loose.
     disjoin, disconnect, disengage, disunite, dissociate, dispair[obs3];
divorce, part, dispart[obs3], detach, separate, cut off, rescind,
segregate; set apart, keep apart; insulate,, isolate; throw out of gear;
cut adrift; loose; unloose, undo, unbind, unchain, unlock &c. (fix) 43,
unpack, unravel; disentangle; set free &c. (liberate) 750.
     sunder, divide, subdivide, sever, dissever, abscind[obs3]; circumcise;
cut; incide|, incise; saw, snip, nib, nip, cleave, rive, rend, slit, split,
splinter, chip, crack, snap, break, tear, burst; rend &c. rend asunder,
rend in twain; wrench, rupture, shatter, shiver, cranch[obs3], crunch,
craunch[obs3], chop; cut up, rip up; hack, hew, slash; whittle; haggle,
hackle, discind|, lacerate, scamble[obs3], mangle, gash, hash, slice.
     cut up, carve, dissect, anatomize; dislimb[obs3]; take to pieces, pull
to pieces, pick to pieces, tear to pieces; tear to tatters, tear piecemeal,
tear limb from limb; divellicate[obs3]; skin &c. 226; disintegrate,
dismember, disbranch[obs3], disband; disperse &c. 73; dislocate, disjoint;
break up; mince; comminute &c. (pulverize) 330; apportion &c. 786.
     part, part company; separate, leave.
     Adj. disjoined   &c. v.; discontinuous &c. 70; multipartite[obs3],
abstract; disjunctive; secant; isolated &c. v.; insular, separate,
disparate, discrete, apart, asunder, far between, loose, free; unattached,
unannexed, unassociated, unconnected; distinct; adrift; straggling; rift,
reft[obs3].
     [capable of being cut] scissile[Chem], divisible, discerptible[obs3],
partible, separable.
     Adv. separately &c. adj.; one by one, severally, apart; adrift,
asunder, in twain; in the abstract, abstractedly.


     #45. [Connecting medium.] Connection. -- N. vinculum, link;
connective, connection; junction &c. 43; bond of union, copula, hyphen,
intermedium[obs3]; bracket; bridge, stepping-stone, isthmus.
     bond, tendon, tendril; fiber; cord, cordage; riband, ribbon, rope,
guy, cable, line, halser|, hawser, painter, moorings, wire, chain; string
&c. (filament) 205.
     fastener, fastening, tie; ligament, ligature; strap; tackle, rigging;
standing rigging, running rigging; traces, harness; yoke; band ribband,
bandage; brace, roller, fillet; inkle[obs3]; with, withe, withy; thong,
braid; girder, tiebeam; girth, girdle, cestus[obs3], garter, halter, noose,
lasso, surcingle, knot, running knot; cabestro [obs3][U. S.], cinch [U.
S.], lariat, legadero[obs3], oxreim[obs3]; suspenders.

<--  p.  16  -->

     pin, corking pin, nail, brad, tack, skewer, staple, corrugated
fastener; clamp, U-clamp, C-clamp; cramp, cramp iron; ratchet, detent,
larigo[obs3], pawl; terret[obs3], treenail, screw, button, buckle; clasp,
hasp, hinge, hank, catch, latch, bolt, latchet[obs3], tag; tooth; hook,
hook and eye; lock, holdfast[obs3], padlock, rivet; anchor, grappling iron,
trennel[obs3], stake, post.
     cement, glue, gum, paste, size, wafer, solder, lute, putty, birdlime,
mortar, stucco, plaster, grout; viscum[obs3].
     shackle, rein &c. (means of restraint) 752; prop &c. (support) 215.
     V. bridge over, span; connect &c. 43;  hang &c. 214.



     #46. Coherence. -- N. coherence, adherence, adhesion, adhesiveness;
concretion accretion; conglutination, agglutination, agglomeration;
aggregation; consolidation, set, cementation; sticking, soldering &c. v.;
connection; dependence.
     tenacity, toughness; stickiness &c. 352; inseparability,
inseparableness; bur, remora.
     conglomerate, concrete &c. (density) 321.
     V. cohere, adhere, stick, cling, cleave, hold, take hold of, hold
fast, close with, clasp, hug; grow together, hang together; twine round &c.
(join) 43.
     stick like a leech, stick like wax; stick close;
cling like ivy, cling like a bur; adhere like a remora, adhere like
Dejanira's shirt.
     glue; agglutinate, conglutinate[obs3]; cement, lute, paste, gum;
solder, weld; cake, consolidate &c. (solidify) 321; agglomerate.
Adj. cohesive, adhesive, adhering, cohering &c. v.; tenacious, tough;
sticky &c. 352.
     united, unseparated, unsessile[obs3], inseparable, inextricable,
infrangible[obs3]; compact &c. (dense) 321.


     #47. [Want of adhesion, nonadhesion, immiscibility.] Incoherence. - N.
nonadhesion[obs3]; immiscibility; incoherence; looseness &c. adj.; laxity;
relaxation; loosening &c. v.; freedom; disjunction &c. 44; rope of sand.
     V. make loose &c. adj.; loosen, slacken, relax; unglue &c. 46; detach
&c. (disjoin) 44.
     Adj. nonadhesive, immiscible; incoherent, detached, loose, baggy,
slack, lax, relaxed, flapping, streaming; disheveled; segregated, like
grains of sand unconsolidated &c. 231, uncombined &c. 48;
noncohesive[obs3].



     #48. Combination. -- N. combination; mixture &c. 41; junction &c. 43;
union, unification, synthesis, incorporation, amalgamation, embodiment,
coalescence, crasis[obs3], fusion, blending, absorption, centralization.
     alloy, compound, amalgam, composition, tertium quid[Lat]; resultant,
impregnation.
     V. combine, unite, incorporate, amalgamate, embody, absorb,
reembody[obs3], blend, merge, fuse, melt into one, consolidate, coalesce,
centralize, impregnate; put together, lump together; cement a union, marry.
     Adj. combined &c. v.; impregnated with, ingrained; imbued inoculated.

     #49. Decomposition. -- N. decomposition, analysis, dissection,
resolution, catalysis, dissolution; corruption &c. (uncleanness) 653;
dispersion &c. 73; disjunction &c. 44; disintegration.
     V. decompose, decompound; analyze, disembody, dissolve; resolve into
its elements, separate into its elements; electrolyze[Chem]; dissect,
decentralize, break up; disperse &c. 73; unravel &c. (unroll) 313; crumble
into dust.
     Adj. decomposed &c. v.; catalytic, analytical; resolvent, separative,
solvent.


<--  p.  17 -->

               4. CONCRETE QUANTITY

     #50. Whole. [Principal part.] -- N. whole, totality, integrity;
totalness &c. adj[obs3].; entirety, ensemble, collectiveness[obs3]; unity
&c. 87; completeness &c. 52;  indivisibility, indiscerptibility[obs3];
integration, embodiment; integer.
     all, the whole, total, aggregate, one and all, gross amount, sum, sum
total, tout ensemble, length and breadth of,
Alpha and Omega, " be all and end all "; complex, complexus [obs3]; lock
stock and barrel.
     bulk, mass, lump, tissue, staple, body, compages[obs3]; trunk, torso,
bole, hull, hulk, skeleton greater part,  major part, best part, principal
part, main part; essential part &c. (importance). 642; lion's share,
Benjamin's mess; the long and the short; nearly, all, almost all.
     V. form a whole, constitute a whole; integrate, embody, amass;
aggregate &c. (assemble) 72; amount to, come to.
     Adj. whole, total, integral, entire; complete &c. 52; one, individual.
     unbroken, intact, uncut, undivided, unsevered[obs3], unclipped[obs3],
uncropped, unshorn; seamless; undiminished; undemolished, undissolved,
undestroyed, unbruised.
     indivisible, indissoluble, indissolvable[obs3], indiscerptible[obs3].
     wholesale, sweeping; comprehensive.
     Adv. wholly, altogether; totally &c. (completely) 52; entirely, all,
all in all, as a whole, wholesale, in a body, collectively, all put
together; in the aggregate, in the lump, in the mass, in the gross, in the
main, in the long run; en masse, as a body, on the whole, bodily|!, en
bloc, in extenso[Lat], throughout, every inch; substantially.
     Phr. tout bien ou rien[Fr].



     #51. Part. -- N. part, portion; dose; item, particular; aught, any;
division, ward; subdivision, section; chapter, clause, count, paragraph,
verse; article, passage; sector, segment; fraction, fragment; cantle,
frustum; detachment, parcel.
     piece[Fr], lump, bit cut, cutting; chip, chunk, collop[obs3], slice,
scale; lamina &c. 204; small part; morsel, particle &c. (smallness) 32;
installment, dividend; share &c. (allotment) 786.
     debris, odds and ends, oddments, detritus; excerpta[obs3]; member,
limb, lobe, lobule, arm, wing, scion, branch, bough, joint, link, offshoot,
ramification, twig, bush, spray, sprig; runner; leaf, leaflet; stump;
component part &c. 56; sarmentum[obs3].
     compartment; department &c. (class) 75; county &c. (region) 181.
     V. part, divide, break &c. (disjoin) 44; partition &c. (apportion)
786.
     Adj. fractional, fragmentary; sectional, aliquot; divided &c. v.; in
compartments, multifid[obs3]; disconnected; partial.
     Adv. partly, in part, partially; piecemeal, part by part; by by
installments,by snatches, by inches, by driblets; bit by bit, inch by inch,
foot by foot, drop by drop; in detail, in lots.)";

bool compare_strlen (my_string const& lhs, my_string const& rhs) {
	if (!lhs || !rhs) return lhs<rhs;
  return (lhs->length() < rhs->length());
}

int main () {
  auto start = std::chrono::high_resolution_clock::now();
  
  std::vector<my_string> words;

  /* Extract words from the input file, splitting on whitespace */
  {
    std::string str;
    std::stringstream ss{ std::string(buff) };
    while (ss >> str) {
      words.push_back(make_string(str));
    }
  }

  /* Extract unique words and count the number of occurances of each word */
  typedef std::unordered_set<my_string, hash_string, equal_ptrs_by_value> my_set;
  //typedef std::set<my_string, order_ptrs_by_value> my_set;
  my_set unique_words;
  typedef std::unordered_map<my_string,int, hash_string, equal_ptrs_by_value> my_map;
  //typedef std::map<my_string,int, order_ptrs_by_value> my_map;
  my_map word_count; 
  for (auto&& s:words) {
    unique_words.insert(s);
    word_count[std::move(s)]++;
  }

  words.clear();

  std::copy(unique_words.begin(), unique_words.end(),
            std::back_inserter(words));

  // Sort by word length 
  std::sort(words.begin(), words.end(), compare_strlen);

  // Print words with length and number of occurances
  for (auto&& word:words) {
    std::cout << word->length() << " " << word_count[word]  << " " <<
              *word << "\n";
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto delta = end-start;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count()/1000. << "seconds \n";
  return 0;
}

