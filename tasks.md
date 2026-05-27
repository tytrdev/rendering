Each step below is one focused session producing a concrete artifact: a PNG, a Shadertoy, a single executable, or a single asset. No tutorials watched, no libraries beyond a window/keyboard layer (SDL, GLFW) and a math vector type you write yourself.

**Phase 1 — Software rasterizer (tinyrenderer, one lesson per day):**
1. Bresenham line, output PPM
2. Triangle fill via barycentric coords
3. Z-buffer, render head model
4. Perspective projection (derive the matrix yourself)
5. Camera/lookAt matrix
6. Programmable-shader abstraction in C++
7. Tangent-space normal mapping
8. Shadow mapping (second pass from light)
9. Screen-space AO

**Phase 2 — Ray tracing.** Ray Tracing in One Weekend, one chapter per day, PNG output each time. Then The Next Week through chapter 7 (BVH, textures, lights, volumes). Stop there.

**Phase 3 — Real-time shaders.** Pick OpenGL 4.5 or WebGL2.
1. Triangle, uniforms, mouse input
2. Phong + Blinn-Phong from scratch
3. Cubemap skybox sampled in fragment shader
4. SDF raymarched sphere on Shadertoy
5. SDF boolean ops + soft shadows + normals-by-gradient
6. Domain repetition + fog

**Phase 4 — PBR:**
1. Microfacet theory on paper: D, G, F derivations
2. GGX + Smith G + Schlick Fresnel in a shader on a single sphere
3. Diffuse irradiance cubemap (offline convolve)
4. Specular prefiltered cubemap + BRDF LUT
5. Combine into a full IBL pass
Reference: Filament documentation, Karis 2013 SIGGRAPH notes.

**Phase 5a — Environment systems.**

Sky/atmosphere:
1. Nishita 1993 single scattering, raymarched fragment shader
2. Hillaire 2020 production sky (sky-view + transmittance LUTs)
3. Volumetric clouds: Schneider/Häggström 2015, noise textures + Henyey-Greenstein

Water:
1. Sum-of-sines plane
2. Gerstner waves with analytic normals
3. Tessendorf 2001 FFT ocean — CPU IFFT first, then compute shader

Terrain:
1. Heightmap raymarched on Shadertoy
2. Tessellated heightmap with displacement
3. Geometry clipmaps (Losasso & Hoppe 2004)

Lighting/GI:
1. Cascaded shadow maps
2. Light probes (irradiance volumes)
3. Screen-space reflections
4. Read the DDGI paper, implement a small grid

**Phase 5b — Production vegetation.**

Procedural tree geometry:
1. 2D L-system turtle graphics → PNG
2. 3D L-system extruding cylinders → OBJ
3. Weber & Penn 1995, implement trunk taper + branching ratios
4. Phyllotaxis branch placement
5. Leaf-card cluster placement (Crytek-style fronds)
6. Export OBJ with per-vertex wind attributes (trunk/branch/leaf weights)

Tree shading:
1. Triplanar bark (albedo + normal, no UV unwrap)
2. Bark with parallax occlusion mapping
3. Leaf-card alpha clip + two-sided lighting
4. Wrap diffuse + back-light transmission — Frostbite "Photorealistic Real-Time Rendering" SIGGRAPH 2014, foliage section
5. Canopy/spherical normals — store smoothed canopy normal per leaf card (Witcher 3 vegetation talk)
6. Hierarchical vertex-shader wind: trunk + branch + leaf, blended by stored attributes (CryEngine vegetation talk)

Tree LOD:
1. Manual LOD0/1/2 by geometry decimation
2. Single-axis billboard from rendered atlas
3. Octahedral impostor capture (Ryan Brucks Epic talk)
4. Octahedral impostor shader with parallax correction
5. Dithered LOD crossfade

Flowers & small plants:
1. Hand-authored cluster mesh, instanced with hash-based color/scale variation
2. Stem-bend wind via single pivot
3. Petal alpha cards with two-sided wrap lighting

Vines:
1. Catmull-Rom spline → extruded tube mesh
2. Vine that walks across an SDF surface, oriented to surface normal
3. Leaves/tendrils placed along spline arc length with twist

Moss & lichen:
1. Shell texturing: N stacked extrusions along normal with alpha mask
2. Procedural mask: dot(N, up) + worley/perlin, drives shell density
3. Triplanar moss/grass overlay shader, drop onto any rock or trunk

Ground-cover ecosystem:
1. Poisson-disk distribution, GPU-instanced
2. Compute-shader frustum + distance culling, indirect draw
3. Density and species masks painted on terrain texture
4. Read "Ghost of Tsushima: Foliage" (GDC 2021) or "Horizon Zero Dawn: Vegetation" — replicate one technique end-to-end
5. Global wind noise texture sampled in world space across all instances

**Phase 5c — Buildings & architecture.**

Modular kit fundamentals:
1. Author a 1m grid; build wall/floor/ceiling/corner kit by hand
2. Trim sheet: one texture covering pipes/panels/edges, UV multiple meshes to it
3. Tileable PBR material from photo or procedural
4. Detail mesh library (bolts, vents, panels), instanced and grid-snapped
5. Deferred decal projection shader
6. Reference: Joel Burgess "Skyrim's Modular Approach" GDC 2013, Thiago Klafke modular workflow

Procedural buildings (shape grammars):
1. Read Müller et al. "Procedural Modeling of Buildings" 2006
2. Split rules: subdivide a box into floors, then into wall panels
3. Window/door placement via grammar
4. Roof generation (hip, gable, mansard)
5. Greeble system: rule-based detail mesh placement on flat surfaces
6. Wang tiles / socket system for connecting kit pieces

Weathering & storytelling:
1. Curvature-based edge wear shader
2. World-space dirt accumulation (top-down driven)
3. Layered material shader: 3–4 PBR materials blended by height + noise + mask
4. Damage decal library with procedural placement

Interiors:
1. Interior parallax mapping for fake rooms behind windows (Joost van Dongen "Interior Mapping")
2. Real interior lighting: emissive area lights + IES profiles
3. God rays through windows using your existing volumetric scattering

Architectural styles (one production-quality building per style):
1. Medieval: half-timbered structure with stone base, thatch roof, heavy weathering
2. Modern: glass tower segment with parallax interior shader on windows
3. Industrial: warehouse module with pipes, rust via worley + curvature edge wear
4. Sci-fi: paneled hull with emissive trim lighting, hard-surface kit, greebles
5. Exotic: pick one — Moorish arch, Japanese pagoda, Mesoamerican step pyramid — ornament tiling via trim sheet

Cities/villages:
1. Hand-place kit pieces with connectivity rules
2. Wave Function Collapse for layout — read Maxim Gumin's repo, implement core algorithm
3. Procedural street/path placement on a heightmap, building plot subdivision

**Phase 6 — Stylized rendering.**

Core stylization:
1. Cel/toon ramp shading
2. Inverted-hull outlines + post-process Sobel outlines
3. Kuwahara filter post-process (painterly)
4. Stylized sky: vertical gradient + procedural shaped clouds (Ghibli sky GDC + ArtStation breakdowns)
5. Stepped specular for anime metal/hair
6. Guilty Gear Xrd "Art of Fighting Game Graphics" GDC — replicate normal editing on faces
7. BotW GDC 2017: hemispheric ambient + wind

Stylized vegetation:
1. BotW grass: per-blade view-dependent normal, hash color, wind from global noise
2. Ghibli tree: hand-painted leaf-cluster texture, careful silhouette cards, no specular, soft hemispheric AO
3. Genshin-style anime grass: stepped color bands, rim term, no PBR
4. Stylized stepped-shell moss
5. Painterly leaves via selective Kuwahara on foliage object IDs

Stylized buildings:
1. Ghibli architecture: hand-painted texture look on modular kit, exaggerated silhouettes
2. Anime city: stepped lighting, strong rim, oversaturated emissive trim
3. Toon-shaded sci-fi panels with outline emphasis on panel seams
4. Genshin-style stylized stone and wood materials

**Phase 7 — Capstone.** One small scene integrating:
- Atmosphere + sky + volumetric clouds
- Terrain with water
- A procedurally generated tree built end-to-end (procedural geometry → triplanar bark → translucent leaves → hierarchical wind → octahedral impostor at distance)
- Flowers, vines on a structure, moss on rocks
- At least two buildings from a modular kit you authored, weathered procedurally, with interior lighting visible through parallax windows
- PBR throughout

Then re-skin the entire scene as a Ghibli variant: same geometry, fully stylized shading pass, painterly post-process. One feature per day until done.

Skip when stuck: if a step exceeds two sessions, ship the uglier version and continue. Come back with more context later.
