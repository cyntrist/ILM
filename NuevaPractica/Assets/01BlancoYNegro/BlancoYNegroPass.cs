using System.Numerics;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.RenderGraphModule;
using UnityEngine.Rendering.RenderGraphModule.Util;
using UnityEngine.Rendering.Universal;

class BlancoYNegroPass : ScriptableRenderPass
{
    private float _factor;
    private Material _material;
    private int materialID;

    public void Setup(float factor, Material material)
    {
        _factor = factor; // me lo pasan desde la render feature
        _material = material;

        materialID = Shader.PropertyToID("_factor");
    }

    // This class stores the data needed by the RenderGraph pass.
    // It is passed as a parameter to the delegate function that executes the RenderGraph pass.
    private class PassData
    {
        public float factor;
        public Material material;

        public TextureHandle destination;
    }

    static void ExecutePass(PassData data, RasterGraphContext context)
    {
        if (data.factor <= 0)
            return;

        UnityEngine.Vector4 scale_offset = new UnityEngine.Vector4(1.0f, 1.0f, 0.0f, 0.0f);
        Blitter.BlitTexture(context.cmd, data.destination, scale_offset, 0, false);
    }

    public override void RecordRenderGraph(RenderGraph renderGraph, ContextContainer frameData)
    {
        // anadimos un nodo en el grafo y ese nodo va a recibir en su funcion de renderizado un pass data
        using (var builder = renderGraph.AddRasterRenderPass<PassData>("BlancoYNegro", out var passData)) // devuelve un constructor de nodo, con esto se abre y luego hay que cerrarlo
        {
            // AQUI NO SE EJECUTA NADA, el orden de muchas de estas cosas dan igual porque aqui solo se apuntan para cuando tengan que ejecutarse

            // frame data es un contenedor de muchas cosas, con el get coges el objeto que sea de ese tipo (solo habra uno)
            UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();

            // la textura en la que estbamos escupiendo cosas
            var source = resourceData.activeColorTexture;

            // creamos la textura/target/destino nueva
            // le pedimos al render graph que cree una textura, un recurso que el propio render graph gestionara, sera el responsable de su ciclo de vida
            var destinationDesc = renderGraph.GetTextureDesc(source);
            destinationDesc.name = $"BlancoYNegro-{passName}";
            TextureHandle destination = renderGraph.CreateTexture(destinationDesc);

            builder.SetRenderAttachment(destination, 0, AccessFlags.Write);
            builder.SetRenderFunc<PassData>(ExecutePass); // le decimos que funcion queremos que se use para renderizar

            _material.SetFloat(materialID, _factor);
            passData.material = _material; // lo que nosotros pongamos aqui terminara en el ExecutePass

            passData.destination = source;

            builder.AllowPassCulling(false); // forzamos al render graph para que no elimine la pasada, ya que si no se usa la pasada el render graph la eliminara por eficiencia
        }
    }
}
