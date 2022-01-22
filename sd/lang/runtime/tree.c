/**
 * This files contains definitions
 * for `u_obj` creation and basic
 * tree manipulation
 */

inline void mkchild (Obj* root, ref_t ty, void* ref) {

	Obj obj = {
		.cdno = 0,
		.rty = ty,
		.oid = child_oid (root);

		.ref = ref,
		.pr = root,
		.cd = 0x00
	};

	root->chno++;
	root->cd = obj;

}
