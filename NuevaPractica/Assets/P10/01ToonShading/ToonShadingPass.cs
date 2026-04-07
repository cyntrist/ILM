using System.Numerics;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.RenderGraphModule;
using UnityEngine.Rendering.RenderGraphModule.Util;
using UnityEngine.Rendering.Universal;

public class ToonShadingPass : ScriptableRenderPass
{
    private int _factor;

    public void Setup(int factor)
    {
        _factor = factor; // me lo pasan desde la render feature
    }

    private class PassData
    {
        public int factor;
    }

    static void ExecutePass(PassData data, RasterGraphContext context)
    {
        
    }

    public override void RecordRenderGraph(RenderGraph renderGraph, ContextContainer frameData)
    {
        // anadimos un nodo en el grafo y ese nodo va a recibir en su funcion de renderizado un pass data
        using (var builder = renderGraph.AddRasterRenderPass<PassData>("ToonShading", out var passData)) // devuelve un constructor de nodo, con esto se abre y luego hay que cerrarlo
        {
            UniversalResourceData resourceData = frameData.Get<UniversalResourceData>();
            var source = resourceData.activeColorTexture;
            var destinationDesc = renderGraph.GetTextureDesc(source);
            destinationDesc.name = $"ToonShading-{passName}";
            TextureHandle destination = renderGraph.CreateTexture(destinationDesc);


            builder.SetRenderAttachment(destination, 0, AccessFlags.Write);
            builder.SetRenderFunc<PassData>(ExecutePass);

            passData.factor = _factor; // lo que nosotros pongamos aqui terminara en el ExecutePass

            builder.AllowPassCulling(false);
        }
    }
}
